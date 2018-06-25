using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Bookstore.Models
{
   public class UserModel
   {
      // TODO: Move to BE
      public String Username
      {
         get => HttpContext.Current.Application["username"] as String;
         set { HttpContext.Current.Application["username"] = value; }
      }
   }
}