# Windowsƽ̨��Qt��pro�ļ��޸�
# INCLUDEPATH ͷ�ļ�·��
INCLUDEPATH +=  D:\QTOpenCV\include\opencv\
                D:\QTOpenCV\include\opencv2\
                D:\QTOpenCV\include

# LIBS ���ļ���-Lָ����·�� -llibָ�������õ���lib��
# ʹ�����淽���������п�
# LIBS += -L D:\QTOpenCV\lib\libopencv_*.a
# ��ʹ�����淽��ֻ����Ҫʹ�õĿ�
LIBS += -L D:\QTOpenCV\lib\
        -llibopencv_highgui320.dll.a\
		-llibopencv_imgproc320.dll.a
		
		
# Ubuntuϵͳ��Qt��OpenCV������װ
# ��װQt5
sudo apt-get install cmake qt5-default qtcreator
# ��װopencv
sudo apt-get install libopencv-dev
sudo apt-get install libcv-dev 

INCLUDEPATH += /usr/include\
			   /usr/include/opencv\
			   /usr/include/opencv2
LIBS += -L/usr/lib\
		-llibopencv_highgui\
		-llibopencv_core\
		-llibopencv_imgproc\
		-llibopencv_calib3d