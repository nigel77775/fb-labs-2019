using System;

namespace laaaab1
{
	class Program
	{
		
		
public const string Alfavit = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
public static int sizeAlfavit = 33;
public static int abc = 0;
public static int ab = 0;
public static unsafe int[] bigram;
public static double c_monograms = 0;
public static double c_bigrams = 0;


public static double enthropy = 0;
public static double chastota = 0;

public static int[] monograms = new int[33];

public static void Sortirovka()
{
	   int peremenn;
	   char peremen;
	   int a = 0;
	   int b = 0;
	   while (a < sizeAlfavit){
	   	while (b < sizeAlfavit - a - 1){
	   		if (monograms[b] < monograms [b+1]){
	   			peremenn = monograms[b];
				monograms[b] = monograms[b + 1];
				monograms[b + 1] = peremenn;}
	   		
	   		if (monograms[b] < monograms [b+1]){			
				peremen = Alfavit[b];
				Alfavit[b] = Alfavit[b + 1];
				Alfavit[b + 1] = peremen;
	   		}
	   		b++;
	   	}
	   	a++;
	   }
	   }

private unsafe void C_Monograms(char * text, ref string Alfavit)
{
	 char per;
	 while (*text != 0)
	 {
		 per = char.ToLower(*text);
		 int a = 0;
		 while ( a < sizeAlfavit){
		 	if ( per == Alfavit[a]){
		 		monograms[a]++;
		 		c_monograms++;
		 	}
		 	a++;
		 }
text++;
	 }
}


private unsafe void C_Bigrams(char * text, ref string Alfavit)
{

  char pred = NULL;
  while (*text != 0)
  {
	char curr = char.ToLower(*text);
	char pred_ = find(Alfavit, Alfavit.Substring(abc), pred);
	char curr_ = find(Alfavit, Alfavit.Substring(abc), curr);

	if ( /*ab % 2 == 0 &&*/  pred_ != Alfavit.Substring(abc) && curr_ != Alfavit.Substring(abc))
	{
	  bigram[pred_ - Alfavit][curr_ - Alfavit]++;
	  c_bigrams++;
}
	}
	  ab++;
	pred = curr;

	text = text.Substring(1);
  }
}

private static void S_Bigrams(ref string filename, ref string Alfavit)
{

  StreamWriter sw = new StreamWriter();
  sw.open(filename);

  sw.WriteLine("     ");
  a = 0;
  b = 0;
  while (a < abc){
  	ofs << Alfavit[a] << "   ";
  	a++;
    ofs << "\n";
    while( b < abc){
    	sw.WriteLine (Alfavit [b]);
    	sw.WriteLine ("  ");
    	b++;
    	
    	while ( a < abc){
    		sw.width(4);
    		sw.WriteLine (bigram[a][b]);
    		sw.WriteLine("  ");
    		a++;
    	}
    }
    sw.close();
  }
 
  
  

private static double EnthropiyaMonograms()
{
chastota = 0;
entropiya = 0;
Sortirovka();
a = 0;
while ( a < sizeAlfavi){
	chastota = ( monograms[a] / c_monograms);
	a++;
}
		 if (chastota != 0)
		 {
		  Console.Write(Alfavit[i]);
		  Console.Write(" ");
		  Console.Write(monograms[i]);
		  Console.Write(" ");
		  Console.Write(chastota);
		  Console.Write("\n");
		  enthropiya = entropiya - (chastota * (Math.Log(chastota) / Math.Log(2)));
		 }
  }

return enthropiya;
}

private static double EnthropiyaBigrams()
{
	enthropiya = 0;
	int a = 0;
	int b = 0;
	chastota = 0;
	while ( a < abc){
		while (b < abc){
			chastota = ([bigram[a][b] / c_bigrams);
			             if (chastota != 0)
			             {
			             	enthropiya = entropiya - ( chastota * (Math.Log(chastota) / Math.Log(2)));
			             }
			             b++;
			}
		a++;
	}
 return enthropiya;

}


static void Main(string[] args)  

 {
	setlocale(LC_ALL,"rus");

	string str;
	ifstream file = new ifstream();

	file.open("text.txt");
	getline(file, str, '\0');
	file.close();

 string input_text = new string(new char[str.Length]);
 input_text = str;

  abc = sizeof(Alfavit) - 1;
  bigram = new int[abc];
  int a = 0;
  int b = 0;
  while (a < abc){
  	bigram[a] = new int[abc];
  	while ( b < abc) {
  		bigram [a][b] = 0;
  		b++;
  	}
  	a++;
  }
  
  unsafe {
  C_Bigrams(input_text);
  S_Bigrams("bigrams неперекрёстные.txt", Alfavit);
  C_Monograms(input_text);
  }
Console.Write("\n");
Console.Write("H1  : ");
Console.Write(EnthropiyaMonograms());
Console.Write("\n");
Console.Write ("H2 : ");
Console.Write(EnthropiyaBigrams());
Console.Write("\n");
Console.Write("Символов в тексте: ");
Console.Write((int)c_monograms);
Console.Write("\n");
Console.Write("Биграмм в тексте: ");
Console.Write((int)c_bigrams);
Console.Write("\n");
return 0;
}
	}
}










