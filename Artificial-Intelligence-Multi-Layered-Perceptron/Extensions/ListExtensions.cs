﻿using System.Collections.Generic;

namespace MultiLayeredPerceptron.Extensions
{
   internal class ListExtensions
   {
      public static string ToString<T>(IEnumerable<T> list)
      {
         return string.Join(",", list);
      }
   }
}