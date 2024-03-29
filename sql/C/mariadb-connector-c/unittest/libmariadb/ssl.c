/************************************************************************************
  Copyright (C) 2012 Monty Program AB

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Library General Public
  License as published by the Free Software Foundation; either
  version 2 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Library General Public License for more details.

  You should have received a copy of the GNU Library General Public
  License along with this library; if not see <http://www.gnu.org/licenses>
  or write to the Free Software Foundation, Inc.,
  51 Franklin St., Fifth Floor, Boston, MA 02110, USA
 *************************************************************************************/

#include "my_test.h"
#include <ma_pthread.h>

static int skip_ssl= 1;

#ifdef WIN32
#define pthread_exit(A) _endthreadex(0)
#endif

const char *ssluser= "ssluser";
const char *sslpw= "sslpw";
char sslhost[128];

pthread_mutex_t LOCK_test;

int check_skip_ssl()
{
#ifndef HAVE_TLS
  diag("client library built without OpenSSL support -> skip");
  return 1;
#endif
  if (skip_ssl)
  {
    diag("server doesn't support SSL -> skip");
    return 1;
  }
  return 0;
}

static int check_cipher(MYSQL *mysql)
{
  char *cipher= (char *)mysql_get_ssl_cipher(mysql);
  if (!cipher)
    return 1;
  diag("cipher: %s", cipher);

  return 0;
}

static int create_ssl_user(const char *ssluser, my_bool is_X509)
{
  int rc;
  char query[1024];
  MYSQL *mysql= mysql_init(NULL);

  FAIL_IF(!mysql_real_connect(mysql, hostname, username, password, schema,
                         port, socketname, 0), mysql_error(mysql));

  sprintf(query, "DROP USER IF EXISTS '%s'@'%s'", ssluser, sslhost);
  rc= mysql_query(mysql, query);
  check_mysql_rc(rc,mysql);

  sprintf(query, "CREATE USER '%s'@'%s' IDENTIFIED BY '%s'", ssluser, sslhost, sslpw);
  rc= mysql_query(mysql, query);
  check_mysql_rc(rc,mysql);

  sprintf(query, "GRANT ALL ON %s.* TO  '%s'@'%s' REQUIRE %s", schema, ssluser, sslhost, is_X509 ? "X509" : "SSL");
  rc= mysql_query(mysql, query);
  check_mysql_rc(rc,mysql);
  rc= mysql_query(mysql, "FLUSH PRIVILEGES");
  check_mysql_rc(rc,mysql);

  mysql_close(mysql);

  return rc;
}

static int test_ssl(MYSQL *mysql)
{
  int rc;
  MYSQL_RES *res;
  MYSQL_ROW row;

  rc= mysql_query(mysql, "SELECT @@have_ssl UNION SELECT @@have_openssl");
  check_mysql_rc(rc, mysql);

  res= mysql_store_result(mysql);
  FAIL_IF(!res, mysql_error(mysql));

  while ((row= mysql_fetch_row(res)))
  {
    if (!strcmp(row[0], "YES"))
      skip_ssl= 0;
    diag("SSL: %s", row[0]);
  }
  mysql_free_result(res);

#ifdef HAVE_GNUTLS
  diag("SSL library: GNUTLS");
#elif HAVE_OPENSSL
  diag("SSL library: OPENSSL");
#elif HAVE_SCHANNEL
  diag("SSL library: SCHANNEL");
#endif  

  sslhost[0]= 0;

  if (!skip_ssl)
  {
    char *p;

    rc= mysql_query(mysql, "SELECT CURRENT_USER()");
    check_mysql_rc(rc, mysql);
    res= mysql_store_result(mysql);
    row= mysql_fetch_row(res);
    diag("user: %s", row[0]);
    if (p= strchr(row[0], '@'))
      strcpy(sslhost, p+1);
    mysql_free_result(res);
  }

  return OK;
}

static int test_ssl_cipher(MYSQL *unused)
{
  MYSQL *my;
  MYSQL_RES *res;
  MYSQL_ROW row;
  int rc;
  
  if (check_skip_ssl())
    return SKIP;

  my= mysql_init(NULL);
  FAIL_IF(!my, "mysql_init() failed");

  mysql_ssl_set(my,0, 0, "/home/wallace/workSPACE/SourceCode/SQL/C/mariadb-connector-c/unittest/libmariadb/certs/ca-cert.pem", 0, 0);

  FAIL_IF(!mysql_real_connect(my, hostname, ssluser, sslpw, schema,
                         port, socketname, 0), mysql_error(my));

  rc= mysql_query(my, "SHOW session status like 'Ssl_version'");
  check_mysql_rc(rc, my);
  res= mysql_store_result(my);
  row= mysql_fetch_row(res);
  diag("%s: %s", row[0], row[1]);
  diag("cipher: %s", mysql_get_ssl_cipher(my));
  mysql_free_result(res);

  FAIL_IF(check_cipher(my) != 0, "Invalid cipher");
  mysql_close(my);
  return OK;
}

static int test_conc95(MYSQL *my)
{
  MYSQL *mysql;

  if (check_skip_ssl())
    return SKIP;

  create_ssl_user("ssluser1", 1);

  mysql= mysql_init(NULL);
  mysql_ssl_set(mysql, 
                "/home/wallace/workSPACE/SourceCode/SQL/C/mariadb-connector-c/unittest/libmariadb/certs/server-key.pem", 
                "/home/wallace/workSPACE/SourceCode/SQL/C/mariadb-connector-c/unittest/libmariadb/certs/server-cert.pem", 
                "/home/wallace/workSPACE/SourceCode/SQL/C/mariadb-connector-c/unittest/libmariadb/certs/ca-cert.pem", 
                NULL, 
                NULL);

  if (!mysql_real_connect(mysql, hostname, "ssluser1", sslpw, schema,
           port, socketname, 0))
  {
    diag("could not establish x509 connection. Error: %s", mysql_error(mysql));
    mysql_close(mysql);
    return FAIL;
  }
  mysql_close(mysql);
  return OK;
}

static int test_multi_ssl_connections(MYSQL *unused)
{
  MYSQL *mysql[50], *my;
  int i, rc;
  int old_connections= 0, new_connections= 0;
  MYSQL_RES *res;
  MYSQL_ROW row;

  if (check_skip_ssl())
    return SKIP;

  diag("Test doesn't work with yassl");
  return SKIP;

  create_ssl_user(ssluser, 0);

  my= mysql_init(NULL);
  FAIL_IF(!my,"mysql_init() failed");
  FAIL_IF(!mysql_real_connect(my, hostname, ssluser, sslpw, schema,
           port, socketname, 0), mysql_error(my));

  rc= mysql_query(my, "SHOW STATUS LIKE 'Ssl_accepts'");
  check_mysql_rc(rc, my);

  res= mysql_store_result(my);
  if ((row= mysql_fetch_row(res)))
    old_connections= atoi(row[1]);
  mysql_free_result(res);

  for (i=0; i < 50; i++)
  {
    mysql[i]= mysql_init(NULL);
    FAIL_IF(!mysql[i],"mysql_init() failed");

    mysql_ssl_set(mysql[i], 0, 0, "/home/wallace/workSPACE/SourceCode/SQL/C/mariadb-connector-c/unittest/libmariadb/certs/ca-cert.pem", 0, 0);

    mysql_real_connect(mysql[i], hostname, ssluser, sslpw, schema,
                         port, socketname, 0);
    if (mysql_errno(mysql[i]))
    {
      diag("loop: %d error: %d %s", i, mysql_errno(mysql[i]), mysql_error(mysql[i]));
      return FAIL;
    }

    FAIL_IF(check_cipher(mysql[i]) != 0, "Invalid cipher");
  }
  for (i=0; i < 50; i++)
    mysql_close(mysql[i]);

  rc= mysql_query(my, "SHOW STATUS LIKE 'Ssl_accepts'");
  check_mysql_rc(rc, my);

  res= mysql_store_result(my);
  if ((row= mysql_fetch_row(res)))
    new_connections= atoi(row[1]);
  mysql_free_result(res);

  mysql_close(my);

  diag("%d SSL connections processed", new_connections - old_connections);
  FAIL_IF(new_connections - old_connections < 50, "new_connections should be at least old_connections + 50");
  return OK;
}

#ifndef WIN32
static void ssl_thread(void *dummy)
#else
DWORD WINAPI ssl_thread(void *dummy)
#endif
{
  MYSQL *mysql= NULL;

  mysql_thread_init();
  
  if (!(mysql= mysql_init(NULL)))
  {  
    mysql_thread_end();
    pthread_exit(NULL);
  }
  mysql_ssl_set(mysql, 0, 0, "/home/wallace/workSPACE/SourceCode/SQL/C/mariadb-connector-c/unittest/libmariadb/certs/ca-cert.pem", 0, 0);

  if(!mysql_real_connect(mysql, hostname, ssluser, sslpw, schema,
          port, socketname, 0))
  {
    diag(">Error: %s", mysql_error(mysql));
    mysql_close(mysql);
    mysql_thread_end();
    pthread_exit(NULL);
  }

  pthread_mutex_lock(&LOCK_test);
  mysql_query(mysql, "UPDATE ssltest SET a=a+1");
  pthread_mutex_unlock(&LOCK_test);
  mysql_close(mysql);
  mysql_thread_end();
  pthread_exit(0);
  return;
}

static int test_ssl_threads(MYSQL *mysql)
{
  int i, rc;
#ifndef WIN32
  pthread_t threads[50];
#else
  HANDLE hthreads[50];
  DWORD dthreads[50];
#endif
  MYSQL_RES *res;
  MYSQL_ROW row;
  
  if (check_skip_ssl())
    return SKIP;

  rc= mysql_query(mysql, "DROP TABLE IF exists ssltest");
  check_mysql_rc(rc, mysql);
  rc= mysql_query(mysql, "CREATE TABLE ssltest (a int)");
  check_mysql_rc(rc, mysql);
  rc= mysql_query(mysql, "INSERT into ssltest VALUES (0)");
  check_mysql_rc(rc, mysql);
  pthread_mutex_init(&LOCK_test, NULL);

  pthread_mutex_init(&LOCK_test, NULL);

  for (i=0; i < 50; i++)
  {
#ifndef WIN32
    pthread_create(&threads[i], NULL, (void *)ssl_thread, NULL);
#else
    hthreads[i]= CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ssl_thread, NULL, 0, &dthreads[i]);
    if (hthreads[i]==NULL)
      diag("error while starting thread");
#endif
  }
  for (i=0; i < 50; i++)
#ifndef WIN32
    pthread_join(threads[i], NULL);
#else
    WaitForSingleObject(hthreads[i], INFINITE);
#endif

  pthread_mutex_destroy(&LOCK_test);

  rc= mysql_query(mysql, "SELECT a FROM ssltest");
  check_mysql_rc(rc, mysql);
  res= mysql_store_result(mysql);
  row= mysql_fetch_row(res);
  diag("Found: %s", row[0]);
  FAIL_IF(strcmp(row[0], "50") != 0, "Expected 50");
  mysql_free_result(res);
  return OK;
}

static int test_phpbug51647(MYSQL *my)
{
  MYSQL* mysql;

  if (check_skip_ssl())
    return SKIP;

  mysql= mysql_init(NULL);
  FAIL_IF(!mysql, "Can't allocate memory");

  mysql_ssl_set(mysql, "/home/wallace/workSPACE/SourceCode/SQL/C/mariadb-connector-c/unittest/libmariadb/certs/client-key.pem", 
                       "/home/wallace/workSPACE/SourceCode/SQL/C/mariadb-connector-c/unittest/libmariadb/certs/client-cert.pem",
                       "/home/wallace/workSPACE/SourceCode/SQL/C/mariadb-connector-c/unittest/libmariadb/certs/ca-cert.pem", 0, 0);

  FAIL_IF(!mysql_real_connect(mysql, hostname, ssluser, sslpw, schema,
           port, socketname, 0), mysql_error(mysql));
  diag("%s", mysql_get_ssl_cipher(mysql));
  mysql_close(mysql);

  return OK;
}

static int test_password_protected(MYSQL *my)
{
  MYSQL* mysql;

  if (check_skip_ssl())
    return SKIP;

  mysql= mysql_init(NULL);
  FAIL_IF(!mysql, "Can't allocate memory");

  mysql_ssl_set(mysql, "/home/wallace/workSPACE/SourceCode/SQL/C/mariadb-connector-c/unittest/libmariadb/certs/client-key-enc.pem", 
                       "/home/wallace/workSPACE/SourceCode/SQL/C/mariadb-connector-c/unittest/libmariadb/certs/client-cert.pem",
                       "/home/wallace/workSPACE/SourceCode/SQL/C/mariadb-connector-c/unittest/libmariadb/certs/ca-cert.pem", 0, 0);

  mysql_options(mysql, MARIADB_OPT_TLS_PASSPHRASE, "qwerty");

  FAIL_IF(!mysql_real_connect(mysql, hostname, ssluser, sslpw, schema,
           port, socketname, 0), mysql_error(mysql));
  diag("%s", mysql_get_ssl_cipher(mysql));
  mysql_close(mysql);

  return OK;
}


static int test_conc50(MYSQL *my)
{
  MYSQL *mysql;

  if (check_skip_ssl())
    return SKIP;

  mysql= mysql_init(NULL);
  FAIL_IF(!mysql, "Can't allocate memory");

  mysql_ssl_set(mysql, NULL, NULL, "/home/wallace/workSPACE/SourceCode/SQL/C/mariadb-connector-c/unittest/libmariadb/certs/my_cert.pem", NULL, NULL);

  mysql_real_connect(mysql, hostname, ssluser, sslpw, schema,
           port, socketname, 0);
  diag("Error: %d %s", mysql_errno(mysql), mysql_error(mysql));
  FAIL_IF(mysql_errno(mysql) != 2026, "Expected errno 2026");
  mysql_close(mysql);

  return OK;
}

static int test_conc50_1(MYSQL *my)
{
  MYSQL *mysql;

  if (check_skip_ssl())
    return SKIP;

  mysql= mysql_init(NULL);
  FAIL_IF(!mysql, "Can't allocate memory");

  mysql_ssl_set(mysql, NULL, NULL, "/home/wallace/workSPACE/SourceCode/SQL/C/mariadb-connector-c/unittest/libmariadb/certs/ca-cert.pem", NULL, NULL);

  mysql_real_connect(mysql, hostname, ssluser, sslpw, schema,
           port, socketname, 0);
  if (mysql_errno(mysql))
    diag("Error: %d %s", mysql_errno(mysql), mysql_error(mysql));
  FAIL_IF(mysql_errno(mysql), "No error expected");
  mysql_close(mysql);

  return OK;
}

static int test_conc50_2(MYSQL *my)
{
  MYSQL *mysql;

  if (check_skip_ssl())
    return SKIP;

  mysql= mysql_init(NULL);
  FAIL_IF(!mysql, "Can't allocate memory");

  mysql_ssl_set(mysql, NULL, NULL, "/home/wallace/workSPACE/SourceCode/SQL/C/mariadb-connector-c/unittest/libmariadb/certs/not-found.pem", NULL, NULL);

  mysql_real_connect(mysql, hostname, ssluser, sslpw, schema,
           port, socketname, 0);
  FAIL_IF(mysql_errno(mysql) != 2026, "Expected errno 2026");
  mysql_close(mysql);

  return OK;
}

static int test_conc127(MYSQL *my)
{
  MYSQL *mysql;

  if (check_skip_ssl())
    return SKIP;

  mysql= mysql_init(NULL);
  FAIL_IF(!mysql, "Can't allocate memory");

  mysql_ssl_set(mysql, NULL, NULL, "/home/wallace/workSPACE/SourceCode/SQL/C/mariadb-connector-c/unittest/libmariadb/certs/dummy.pem", NULL, NULL);

  mysql_real_connect(mysql, hostname, ssluser, sslpw, schema,
           port, socketname, 0);
  diag("Error: %s", mysql_error(mysql));
  FAIL_IF(mysql_errno(mysql) == 0, "Error expected (invalid certificate)");
  mysql_close(mysql);

  return OK;
}

static int test_conc50_3(MYSQL *my)
{
  MYSQL *mysql;

  if (check_skip_ssl())
    return SKIP;

  create_ssl_user(ssluser, 0);

  mysql= mysql_init(NULL);
  FAIL_IF(!mysql, "Can't allocate memory");

  mysql_ssl_set(mysql, NULL, NULL, NULL, NULL, NULL);

  mysql_real_connect(mysql, hostname, ssluser, sslpw, schema,
           port, socketname, 0);
  FAIL_IF(!mysql_errno(mysql), "Error expected, SSL connection required!");
  mysql_close(mysql);

  mysql= mysql_init(NULL);
  FAIL_IF(!mysql, "Can't allocate memory");

  mysql_ssl_set(mysql, NULL, NULL, "/home/wallace/workSPACE/SourceCode/SQL/C/mariadb-connector-c/unittest/libmariadb/certs/ca-cert.pem", NULL, NULL);

  mysql_real_connect(mysql, hostname, ssluser, sslpw, schema,
           port, socketname, 0);
  diag("Error: %s<", mysql_error(mysql));
  FAIL_IF(mysql_errno(mysql), "No error expected");
  mysql_close(mysql);

  return OK;
}

static int test_conc50_4(MYSQL *my)
{
  MYSQL *mysql;

  if (check_skip_ssl())
    return SKIP;

  mysql= mysql_init(NULL);
  FAIL_IF(!mysql, "Can't allocate memory");

  mysql_ssl_set(mysql, NULL, "/home/wallace/workSPACE/SourceCode/SQL/C/mariadb-connector-c/unittest/libmariadb/certs/ca-cert.pem", NULL, NULL, NULL);

  mysql_real_connect(mysql, hostname, ssluser, sslpw, schema,
           port, socketname, 0);
  FAIL_IF(!mysql_errno(mysql) , "Error expected");
  mysql_close(mysql);

  return OK;
}

static int verify_ssl_server_cert(MYSQL *my)
{
  MYSQL *mysql;
  uint verify= 1;

  if (check_skip_ssl())
    return SKIP;

  mysql= mysql_init(NULL);
  FAIL_IF(!mysql, "Can't allocate memory");

  mysql_ssl_set(mysql, NULL, NULL, "/home/wallace/workSPACE/SourceCode/SQL/C/mariadb-connector-c/unittest/libmariadb/certs/ca-cert.pem", NULL, NULL);
  mysql_options(mysql, MYSQL_OPT_SSL_VERIFY_SERVER_CERT, &verify);

  mysql_real_connect(mysql, hostname, ssluser, sslpw, schema,
           port, socketname, 0);

  FAIL_IF(!mysql_errno(mysql), "Expected error");
  mysql_close(mysql);

  return OK;
}

static int test_bug62743(MYSQL *my)
{
  MYSQL *mysql;

  if (check_skip_ssl())
    return SKIP;

  mysql= mysql_init(NULL);
  FAIL_IF(!mysql, "Can't allocate memory");

  mysql_ssl_set(mysql, "dummykey", NULL, NULL, NULL, NULL);

  mysql_real_connect(mysql, hostname, ssluser, sslpw, schema,
           port, socketname, 0);
  diag("Error: %s", mysql_error(mysql));
  FAIL_IF(mysql_errno(mysql) != 2026, "Expected errno 2026");
  mysql_close(mysql);

  mysql= mysql_init(NULL);
  FAIL_IF(!mysql, "Can't allocate memory");

  mysql_ssl_set(mysql, "/home/wallace/workSPACE/SourceCode/SQL/C/mariadb-connector-c/unittest/libmariadb/certs/client-key.pem", NULL, NULL, NULL, NULL);

  mysql_real_connect(mysql, hostname, ssluser, sslpw, schema,
           port, socketname, 0);
  diag("Error with key: %s", mysql_error(mysql));
  FAIL_IF(mysql_errno(mysql) != 2026, "Expected errno 2026");
  mysql_close(mysql);

  mysql= mysql_init(NULL);
  FAIL_IF(!mysql, "Can't allocate memory");

  mysql_ssl_set(mysql, "/home/wallace/workSPACE/SourceCode/SQL/C/mariadb-connector-c/unittest/libmariadb/certs/client-key.pem",
                       "/home/wallace/workSPACE/SourceCode/SQL/C/mariadb-connector-c/unittest/libmariadb/certs/client-cert.pem", NULL, NULL, NULL);

  mysql_real_connect(mysql, hostname, ssluser, sslpw, schema,
           port, socketname, 0);
  FAIL_IF(mysql_errno(mysql) != 0, "Expected no error");
  mysql_close(mysql);

  mysql= mysql_init(NULL);
  FAIL_IF(!mysql, "Can't allocate memory");

  mysql_ssl_set(mysql, "/home/wallace/workSPACE/SourceCode/SQL/C/mariadb-connector-c/unittest/libmariadb/certs/client-key.pem", "blablubb", NULL, NULL, NULL);

  mysql_real_connect(mysql, hostname, ssluser, sslpw, schema,
           port, socketname, 0);
  diag("Error with cert: %s", mysql_error(mysql));
  FAIL_IF(mysql_errno(mysql) == 0, "Expected error");
  mysql_close(mysql);

  return OK;
}

#ifndef WIN32
int thread_conc102(void)
#else
DWORD WINAPI thread_conc102(void)
#endif
{
  MYSQL *mysql;
  int rc;
  MYSQL_RES *res;
  mysql_thread_init();
  mysql= mysql_init(NULL);

  mysql_ssl_set(mysql, "/home/wallace/workSPACE/SourceCode/SQL/C/mariadb-connector-c/unitt/libmariadb/certs/client-key.pem",
                       "/home/wallace/workSPACE/SourceCode/SQL/C/mariadb-connector-c/unittest/libmariadb/certs/client-cert.pem", 
                       "/home/wallace/workSPACE/SourceCode/SQL/C/mariadb-connector-c/unittest/libmariadb/certs/ca-cert.pem", 
                        NULL, NULL);
  mysql_ssl_set(mysql,0, 0, "/home/wallace/workSPACE/SourceCode/SQL/C/mariadb-connector-c/unittest/libmariadb/certs/ca-cert.pem", 0, 0);

  if(!mysql_real_connect(mysql, hostname, username, password, schema,
          port, socketname, 0))
  {
    diag(">Error: %s", mysql_error(mysql));
    goto end;
  }
  if (!mysql_get_ssl_cipher(mysql))
  {
    diag("Error: No ssl connection");
    goto end;
  }
  pthread_mutex_lock(&LOCK_test);
  rc= mysql_query(mysql, "UPDATE t_conc102 SET a=a+1");
  check_mysql_rc(rc, mysql);
  pthread_mutex_unlock(&LOCK_test);
  check_mysql_rc(rc, mysql);
  if (res= mysql_store_result(mysql))
    mysql_free_result(res);
end:
  mysql_close(mysql);
  mysql_thread_end();
  return 0;
}

static int test_conc_102(MYSQL *mysql)
{

  int rc;
  int i;
  MYSQL_ROW row;
  MYSQL_RES *res;
#ifndef WIN32
  pthread_t threads[50];
#else
  HANDLE hthreads[50];
  DWORD threads[50];
#endif

  if (check_skip_ssl())
    return SKIP;

  rc= mysql_query(mysql, "DROP TABLE IF EXISTS t_conc102");
  check_mysql_rc(rc, mysql);
  rc= mysql_query(mysql, "CREATE TABLE t_conc102 ( a int)");
  check_mysql_rc(rc, mysql);
  rc= mysql_query(mysql, "INSERT INTO t_conc102 VALUES (0)");
  check_mysql_rc(rc, mysql);
  pthread_mutex_init(&LOCK_test, NULL);

  for (i=0; i < 50; i++)
  {
#ifndef WIN32
    pthread_create(&threads[i], NULL, (void *)thread_conc102, NULL);
#else
    hthreads[i]= CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)thread_conc102, NULL, 0, &threads[i]);
    if (hthreads[i]==NULL)
      diag("error while starting thread");
#endif
  }
  for (i=0; i < 50; i++)
  {
#ifndef WIN32
    pthread_join(threads[i], NULL);
#else
    WaitForSingleObject(hthreads[i], INFINITE);
#endif
  } 
  pthread_mutex_destroy(&LOCK_test);
  rc= mysql_query(mysql, "SELECT a FROM t_conc102");
  check_mysql_rc(rc, mysql);
  res= mysql_store_result(mysql);
  row= mysql_fetch_row(res);
  diag("Found: %s", row[0]);
  FAIL_IF(strcmp(row[0], "50") != 0, "Expected 50");
  mysql_free_result(res);
  return OK;
}

const char *ssl_cert_finger_print= "";

static int test_ssl_fp(MYSQL *unused)
{
  MYSQL *my;
  MYSQL_RES *res;
  MYSQL_ROW row;
  int rc;
  
  if (check_skip_ssl())
    return SKIP;

  my= mysql_init(NULL);
  FAIL_IF(!my, "mysql_init() failed");

  mysql_ssl_set(my,0, 0, "/home/wallace/workSPACE/SourceCode/SQL/C/mariadb-connector-c/unittest/libmariadb/certs/ca-cert.pem", 0, 0);

  mysql_options(my, MARIADB_OPT_SSL_FP, ssl_cert_finger_print);

  FAIL_IF(!mysql_real_connect(my, hostname, ssluser, sslpw, schema,
                         port, socketname, 0), mysql_error(my));
  
  FAIL_IF(check_cipher(my) != 0, "Invalid cipher");

  rc= mysql_query(my, "SET @a:=1");
  check_mysql_rc(rc, my);

  rc= mysql_query(my, "SELECT @a");
  check_mysql_rc(rc, my);

  if ((res= mysql_store_result(my)))
  {
    row= mysql_fetch_row(res);
    diag("@a:=%s", row[0]);
    mysql_free_result(res);
  }

  mysql_close(my);
  return OK;
}

static int test_ssl_fp_list(MYSQL *unused)
{
  MYSQL *my;
  
  if (check_skip_ssl())
    return SKIP;

  my= mysql_init(NULL);
  FAIL_IF(!my, "mysql_init() failed");

  mysql_ssl_set(my,0, 0, "/home/wallace/workSPACE/SourceCode/SQL/C/mariadb-connector-c/unittest/libmariadb/certs/ca-cert.pem", 0, 0);

  mysql_options(my, MARIADB_OPT_SSL_FP_LIST, "./fingerprint.list");

  FAIL_IF(!mysql_real_connect(my, hostname, ssluser, sslpw, schema,
                         port, socketname, 0), mysql_error(my));

  FAIL_IF(check_cipher(my) != 0, "Invalid cipher");
  mysql_close(my);
  return OK;
}

static int test_ssl_version(MYSQL *mysql)
{
  unsigned int iversion;
  const char *version, *library;
  MYSQL *my;

  if (check_skip_ssl())
    return SKIP;

  my= mysql_init(NULL);
  FAIL_IF(!my, "mysql_init() failed");

  mysql_ssl_set(my,0, 0, "/home/wallace/workSPACE/SourceCode/SQL/C/mariadb-connector-c/unittest/libmariadb/certs/ca-cert.pem", 0, 0);
  FAIL_IF(!mysql_real_connect(my, hostname, ssluser, sslpw, schema,
                         port, socketname, 0), mysql_error(my));

  diag("cipher: %s", mysql_get_ssl_cipher(my));
  mariadb_get_infov(my, MARIADB_CONNECTION_TLS_VERSION_ID, &iversion);
  diag("protocol: %d", iversion);
  mariadb_get_infov(my, MARIADB_CONNECTION_TLS_VERSION, &version);
  diag("protocol: %s", version);

  mariadb_get_infov(my, MARIADB_TLS_LIBRARY, &library);
  diag("library: %s", library);

  mysql_close(my);

  return OK;
}

#ifdef HAVE_SCHANNEL
static int test_schannel_cipher(MYSQL *mysql)
{
  MYSQL *my;
  unsigned int cipher_strength= 256;

  if (check_skip_ssl())
    return SKIP;

  my= mysql_init(NULL);
  FAIL_IF(!my, "mysql_init() failed");

  mysql_ssl_set(my,0, 0, "/home/wallace/workSPACE/SourceCode/SQL/C/mariadb-connector-c/unittest/libmariadb/certs/ca-cert.pem", 0, 0);
  mysql_options(my, MARIADB_OPT_TLS_CIPHER_STRENGTH, &cipher_strength);
  FAIL_IF(!mysql_real_connect(my, hostname, ssluser, sslpw, schema,
                         port, socketname, 0), mysql_error(my));

  diag("cipher: %s", mysql_get_ssl_cipher(my));
  FAIL_IF(strcmp(mysql_get_ssl_cipher(my), "CALG_AES_256") != 0, "expected cipher with 256bit strength");

  mysql_close(my);

  return OK;
}

#endif
  

struct my_tests_st my_tests[] = {
  {"test_ssl", test_ssl, TEST_CONNECTION_NEW, 0,  NULL,  NULL},
//  {"test_conc127", test_conc127, TEST_CONNECTION_NEW, 0,  NULL,  NULL},
  {"test_ssl_fp", test_ssl_fp, TEST_CONNECTION_NEW, 0,  NULL,  NULL},
  {"test_ssl_fp_list", test_ssl_fp_list, TEST_CONNECTION_NEW, 0,  NULL,  NULL},
  {"test_conc50", test_conc50, TEST_CONNECTION_NEW, 0,  NULL,  NULL},
  {"test_conc50_1", test_conc50_1, TEST_CONNECTION_NEW, 0,  NULL,  NULL},
  {"test_conc50_2", test_conc50_2, TEST_CONNECTION_NEW, 0,  NULL,  NULL},
  {"test_conc50_3", test_conc50_3, TEST_CONNECTION_NEW, 0,  NULL,  NULL},
  {"test_conc50_4", test_conc50_4, TEST_CONNECTION_NEW, 0,  NULL,  NULL},
  {"test_conc95", test_conc95, TEST_CONNECTION_NEW, 0,  NULL,  NULL},
  {"verify_ssl_server_cert", verify_ssl_server_cert, TEST_CONNECTION_NEW, 0,  NULL,  NULL},
  {"test_bug62743", test_bug62743, TEST_CONNECTION_NEW, 0,  NULL,  NULL}, 
  {"test_phpbug51647", test_phpbug51647, TEST_CONNECTION_NONE, 0, NULL, NULL},
  {"test_ssl_cipher", test_ssl_cipher, TEST_CONNECTION_NONE, 0,  NULL,  NULL},
  {"test_multi_ssl_connections", test_multi_ssl_connections, TEST_CONNECTION_NONE, 0,  NULL,  NULL},
  {"test_conc_102", test_conc_102, TEST_CONNECTION_NEW, 0, NULL, NULL},
  {"test_ssl_version", test_ssl_version, TEST_CONNECTION_NEW, 0, NULL, NULL},
  {"test_ssl_threads", test_ssl_threads, TEST_CONNECTION_NEW, 0,  NULL,  NULL},
#ifndef HAVE_SCHANNEL
  {"test_password_protected", test_password_protected, TEST_CONNECTION_NEW, 0,  NULL,  NULL}, 
#else
  {"test_schannel_cipher", test_schannel_cipher, TEST_CONNECTION_NEW, 0,  NULL,  NULL}, 
#endif
  {NULL, NULL, 0, 0, NULL, NULL}
};


int main(int argc, char **argv)
{
  get_envvars();

  if (argc > 1)
    get_options(argc, argv);

  run_tests(my_tests);

  mysql_server_end();
  return(exit_status());
}

