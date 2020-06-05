using Microsoft.SqlServer.Server;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net.Http.Headers;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace Retele_tema4_TranspositionCipher
{
    class TranspositionCipher
    {
        private static string key;
        private static string text;

        private static void ReadFromFile()
        {
            try
            {
                StreamReader stream = new StreamReader("Input.txt");
                key = stream.ReadLine();
                text = stream.ReadLine();
            } 
            catch (IOException e)
            {
                Console.WriteLine("File could not be read");
                Console.WriteLine(e.Message);
            }
        }

        private static bool Validation()
        {
            for (int index1 = 0; index1 < key.Length - 1; index1++)
            {
                for(int index2 = index1 + 1; index2 < key.Length; index2++)
                {
                    char letter1 = key[index1];
                    char letter2 = key[index2];

                    if (letter1.ToString().Equals(letter2.ToString(), StringComparison.OrdinalIgnoreCase))
                        return false;
                }
            }

            return true;
        }

        private static void GenerateOrder(string key, string alphabet, ref StringBuilder[] line)
        {
            int order = 1;

            for(int index1 = 0; index1 < alphabet.Length; index1++)
            {
                for(int index2 = 0; index2 < key.Length; index2++)
                {
                    if(alphabet[index1] == key[index2])
                    {
                        line[index2].Append(order.ToString());
                        order++;
                    }
                }
            }
        }

        private static void GenerateMatrix(ref StringBuilder[][] matrix, string alphabet)
        {
            for(int index = 0; index < key.Length; index++)
            {
                matrix[0][index].Append(key[index].ToString());
            }

            GenerateOrder(key, alphabet, ref matrix[1]);
            int index1 = 0;
            int index2 = 2;

            while(index1 < text.Length)
            {
                for(int index3 = 0; index3 < key.Length; index3++)
                {
                    if (index1 == text.Length)
                        break;
                    else if(text[index1] == Convert.ToChar(" "))
                    {
                        index3--;
                        index1++;
                    }
                    else
                    {
                        matrix[index2][index3].Append(text[index1].ToString());
                        index1++;
                    }
                }

                index2++;
            }
        }

        private static void AddSurplusLetters(ref StringBuilder[][] matrix, string alphabet)
        {
            if(matrix[matrix.Length - 1][matrix[0].Length - 1].ToString() == "")
            {
                int index1 = 0;
                int index2 = 0;

                while(matrix[matrix.Length - 1][matrix[0].Length - 1].ToString() == "")
                {
                    if (matrix[matrix.Length - 1][index2].ToString() != "")
                        index2++;
                    else
                    {
                        matrix[matrix.Length - 1][index2].Append(alphabet[index1].ToString());
                        index1++;
                        index2++;
                    }
                }
            }
        }

        private static void PrintMatrix(StringBuilder[][] matrix)
        {
            for(int index1 = 0; index1 < matrix.Length; index1++)
            {
                for(int index2 = 0; index2 < matrix[index1].Length; index2++)
                {
                    Console.Write(matrix[index1][index2].ToString());
                }

                Console.Write("\n");
            }
        }

        private static int FindMinimum(StringBuilder[] line, ref int lastMinimum)
        {
            int minimum = 30;
            int minimumIndex = 0;

            for(int index = 0; index < line.Length; index++)
            {
                if (Convert.ToInt32(line[index].ToString()) < minimum && Convert.ToInt32(line[index].ToString()) > lastMinimum)
                {
                    minimum = Convert.ToInt32(line[index].ToString());
                    minimumIndex = index;
                }
            }

            lastMinimum = minimum;
            return minimumIndex;
        }

        private static StringBuilder EncryptedMessage(StringBuilder[][] matrix)
        {
            StringBuilder encryptedMessage = new StringBuilder("");
            int index1 = 0;
            int minimumIndex;
            int lastMinimum = 0;

            while(index1 < matrix[0].Length)
            {
                minimumIndex = FindMinimum(matrix[1],ref lastMinimum);

                for(int index2 = 2; index2 < matrix.Length; index2++)
                {
                    encryptedMessage.Append(matrix[index2][minimumIndex].ToString());
                }

                index1++;
                encryptedMessage.Append(" ");
            }

            return encryptedMessage;
        }

        private static void PrintMessage(StringBuilder encryptedMessage)
        {
            Console.WriteLine(encryptedMessage.ToString());
        }

        static void Main(string[] args)
        {
            ReadFromFile();

            if (Validation())
            {
                int lines = ((text.Length - text.Count(Char.IsWhiteSpace)) / key.Length) + 3;
                StringBuilder[][] matrix = new StringBuilder[lines][];
                string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
                StringBuilder encryptedMessage;

                for(int index1 = 0; index1 < lines; index1++)
                {
                    matrix[index1] = new StringBuilder[key.Length];

                    for(int index2 = 0; index2 < matrix[index1].Length; index2++)
                    {
                        matrix[index1][index2] = new StringBuilder("");
                    }
                }

                GenerateMatrix(ref matrix, alphabet);
                AddSurplusLetters(ref matrix, alphabet);
                Console.WriteLine("The generated matrix:");
                PrintMatrix(matrix);
                encryptedMessage = EncryptedMessage(matrix);
                Console.WriteLine("The encrypted message is: ");
                PrintMessage(encryptedMessage);
            }
            else
                Console.WriteLine("Invalid input.");

            Console.WriteLine("Press any key to exit...");
            Console.ReadKey();
        }
    }
}
