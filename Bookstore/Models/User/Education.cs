using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace Bookstore.Models.User
{
   public static class Education
   {
      public static IList<SelectListItem> List = new List<SelectListItem>();

      static Education()
      {
         // TODO: Pull from database
         List.Add(new SelectListItem { Text = "Primary", Value = "primary", Selected = false });
         List.Add(new SelectListItem { Text = "High school", Value = "highschool", Selected = false });
         List.Add(new SelectListItem { Text = "University", Value = "university", Selected = false });
      }
   }

}