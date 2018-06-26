using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Bookstore.Models
{
   public static class Hobbies
   {
      public static IList<SelectListItem> List = new List<SelectListItem>();

      static Hobbies()
      {
         // TODO: Pull from database
         List.Add(new SelectListItem {Text = "Diving", Value="diving", Selected = false });
         List.Add(new SelectListItem {Text = "Swimming", Value="swimming", Selected = false });
         List.Add(new SelectListItem {Text = "Snorkeling", Value="snorkeling", Selected = false });
         List.Add(new SelectListItem {Text = "Yachting", Value="yachting", Selected = false });
         List.Add(new SelectListItem {Text = "Driving", Value="driving", Selected = false });
      }
   }
}