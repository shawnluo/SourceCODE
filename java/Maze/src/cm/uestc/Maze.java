package cm.uestc;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;
import java.util.Stack;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.SwingConstants;


public class Maze {

	public Maze(int rows,int columns){
		this.rows=rows;
		this.columns=columns;
		
		
	}
	public void getMaze(){
		init();
		generateMaze();
		showMaze();
		answer=null;
	}
	public void getMaze(int rows,int columns){
		this.rows=rows;
		this.columns=columns;
		init();
		generateMaze();
		updateMaze();
		answer=null;
		
		
	}
	private int rows;
	private int columns;
	private DisjSetsSize sets;
	private Node[][] datas;
	private List<Edge> optionEdge;
	private String answer;
	Edge vertical=new Edge(0,0,EdgeType.vertical);
	Edge level=new Edge(0,0,EdgeType.level);
	Edge VISITED=new Edge(0,0,EdgeType.level);
	private void init(){
		//产生一个有所有边的图形rows*columns
		sets=new DisjSetsSize(rows*columns);
		datas=new Node[rows][columns];
		optionEdge=new LinkedList<Edge>();
		for(int i=0;i<rows;i++){
			for(int j=0;j<columns;j++){
				datas[i][j]=new Node(String.valueOf(i*columns+j),i,j);
			}
		}
		for(int j=0;j<columns;j++){
			datas[0][j].up=level;
			datas[rows-1][j].down=level;
		}
		for(int i=0;i<rows;i++){
			datas[i][0].left=vertical;
			datas[i][columns-1].right=vertical;
		}
		for(int i=0;i<rows-1;i++){
			for(int j=0;j<columns;j++){
				datas[i][j].down=new Edge(i*columns+j,(i+1)*columns+j,EdgeType.level);
				datas[i+1][j].up=datas[i][j].down;
				optionEdge.add(datas[i][j].down);
			}
		}
		for(int j=0;j<columns-1;j++){
			for(int i=0;i<rows;i++){
				datas[i][j].right=new Edge(i*columns+j,i*columns+j+1,EdgeType.vertical);
				datas[i][j+1].left=datas[i][j].right;
				optionEdge.add(datas[i][j].right);
			}
		}
		
	}
	private void generateMaze(){
		Random rand=new Random();
		while(!optionEdge.isEmpty()){
			int index=rand.nextInt(optionEdge.size());
			Edge choosed=optionEdge.remove(index);
			int first=choosed.first;
			int second=choosed.second;
			int root1=sets.find(first);
			int root2=sets.find(second);
			if(root1!=root2){
				sets.union(root1, root2);
				if(choosed.type==EdgeType.vertical){
					datas[first/columns][first%columns].right=null;
					datas[second/columns][second%columns].left=null;
				}else{
					datas[first/columns][first%columns].down=null;
					datas[second/columns][second%columns].up=null;
				}
			}
		}
	//	System.out.println(sets.toString());
		//处理开始 结尾
		datas[0][0].up=null;
		datas[rows-1][columns-1].down=null;
		
	}
	JFrame frame=new JFrame("Maze");
	JPanel panel=new JPanel();
	private void updateMaze(){
		frame.remove(panel);
		panel=new JPanel();
		frame.add(BorderLayout.CENTER,panel);
		panel.setLayout(new GridLayout(rows, columns));
		for(int i=0;i<rows;i++){
			for(int j=0;j<columns;j++){
				String labelValue=datas[i][j].displayInfo;
				JLabel label=new JLabel(labelValue);
				label.setHorizontalAlignment(SwingConstants.CENTER);
				int up=1,down=1,right=1,left=1;
				if(datas[i][j].up==null){
					up=0;
				}else if(datas[i][j].up==level){
					up=2;
				}
				if(datas[i][j].left==null){
					left=0;
				}else if(datas[i][j].left==vertical){
					left=2;
				}
				if(datas[i][j].down==null){
					down=0;
				}else if(datas[i][j].down==level){
					down=2;
				}
				if(datas[i][j].right==null){
					right=0;
				}else if(datas[i][j].right==vertical){
					right=2;
				}
				label.setBorder(BorderFactory.createMatteBorder(up, left, down, right, Color.BLACK));
				panel.add(label);
			}
		}
		frame.setVisible(true);
	}
	private void showMaze(){
		frame.setSize(440, 440);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setLayout(new BorderLayout());
		JPanel north=new JPanel();
		frame.add(BorderLayout.NORTH,north);
		final JTextArea answer=new JTextArea();
		answer.setColumns(10);
		answer.setRows(3);
		answer.setAutoscrolls(true);
		final JTextField rowsField=new JTextField(String.valueOf(rows));
		rowsField.setSize(100, 20);
		final JTextField columnsField=new JTextField(String.valueOf(columns));
		columnsField.setSize(100, 20);
		JButton generate=new JButton("generate");
		north.add(generate);
		north.add(rowsField);
		north.add(columnsField);
		generate.addActionListener(new ActionListener() {
			
			@Override
			public void actionPerformed(ActionEvent e) {
				answer.setText("");
				getMaze(Integer.valueOf(rowsField.getText()),
						Integer.valueOf(columnsField.getText()));
				
				
			}
		});
		
		frame.add(BorderLayout.EAST,new JLabel("    "));
		frame.add(BorderLayout.WEST,new JLabel("    "));
		frame.add(BorderLayout.CENTER,panel);
		JPanel south=new JPanel();
		frame.add(BorderLayout.SOUTH,south);
		JButton showAnswer=new JButton("show answer");
		south.add(showAnswer);
		south.add(answer);
		showAnswer.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e) {
				String answerStr= getAnswer();
				answer.setText(answerStr);
			}
			
		});
		updateMaze();
	}
	
	public String getAnswer(){
		if(null==answer){
			Stack<Node> stack=new Stack<Node>();
			stack.add(datas[rows-1][columns-1]);
			datas[rows-1][columns-1].down=VISITED;
			while(!stack.isEmpty()&&stack.peek()!=datas[0][0]){
				Node top=stack.peek();
				if(null==top.up){
					stack.push(datas[top.i-1][top.j]);
					top.up=VISITED;
					datas[top.i-1][top.j].down=VISITED;
				}else if(null==top.left){
					stack.push(datas[top.i][top.j-1]);
					top.left=VISITED;
					datas[top.i][top.j-1].right=VISITED;
				}else if(null==top.down){
					stack.push(datas[top.i+1][top.j]);
					top.down=VISITED;
					datas[top.i+1][top.j].up=VISITED;
				}else if(null==top.right){
					stack.push(datas[top.i][top.j+1]);
					top.right=VISITED;
					datas[top.i][top.j+1].left=VISITED;
				}else{
					stack.pop();
				}
			}
			if(stack.isEmpty()){
				return "system error!";
			}
			StringBuilder result=new StringBuilder();
			int i=0;
			while(stack.peek()!=datas[rows-1][columns-1]){
				
				result.append(stack.pop().displayInfo).append("->");
				if(++i%10==0){
					result.append("\n");
				}
			}
			result.append(stack.pop().displayInfo);
			answer=result.toString();
			return result.toString();
		}
		return answer;
	}
	
	private static enum EdgeType{
		vertical,level;
	}
	private static class Edge{
		int first;
		int second;
		EdgeType type;
		public Edge(int first,int second,EdgeType type){
			this.first=first;
			this.second=second;
			this.type=type;
		}
	}
	private static class Node{
		String displayInfo;
		Edge up;
		Edge left;
		Edge down;
		Edge right;
		int i;
		int j;
		public Node(String info,int i,int j){
			this.displayInfo=info;
			this.i=i;
			this.j=j;
		}
	}
	
	public static void main(String[] args){
		Maze maze=new Maze(10, 10);
		maze.getMaze();
	}
}
