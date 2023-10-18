import java.io.File;

public class Main {
  public static void main(String[] args) {
	  String msg = "";
	  
	  for(int i = 1; i != 1001; i++) {
		  File myFile = new File("D:\\Atividade(%d).pdf".formatted(i));
		 
		  try {
			  if (myFile.isFile()) {
				  myFile.delete(); 
				  msg= "Arquivo deletado";
			  }
			  else {
				  myFile.createNewFile(); 
				  msg= "Arquivo criado";
			  }
		  }
		  catch(Exception e) {
			  msg = "Erro!";
		  }
		  finally {
			  System.out.println("[%d] %s!".formatted(i, msg));
		  }
	  }
  }
}