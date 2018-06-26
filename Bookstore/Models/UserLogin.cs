using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Web;

namespace Bookstore.Models
{
   public class UserLogin
   {
      [Display(Name = "Username")]
      [Required(ErrorMessage = "The username is required")]
      public String Username
      {
         get => HttpContext.Current.Application["username"] as String;
         set { HttpContext.Current.Application["username"] = value; }
      }

      // TODO Crypto 
      [Display(Name = "Password")]
      [MinLength(8, ErrorMessage = "Password must be at least {1} letters long")]
      [DataType(DataType.Password)]
      [Required(ErrorMessage = "The password is required")]
      public String Password
      {
         get => HttpContext.Current.Application["password"] as String;
         set { HttpContext.Current.Application["password"] = value; }
      }
   }
}