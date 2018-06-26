using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Web;

namespace Bookstore.Models
{
   // TODO: Move to DB
   public class UserModel : UserLogin
   {
      [Display(Name = "Name")]
      [Required(ErrorMessage = "The name is required")]
      public String Name
      {
         get => HttpContext.Current.Application["name"] as String;
         set { HttpContext.Current.Application["name"] = value; }
      }

      [Display(Name = "Surname")]
      [Required(ErrorMessage = "The surname is required")]
      public String Surname
      {
         get => HttpContext.Current.Application["surname"] as String;
         set { HttpContext.Current.Application["surname"] = value; }
      }

      [Display(Name = "Email address")]
      [Required(ErrorMessage = "The email address is required")]
      [EmailAddress(ErrorMessage = "Invalid Email Address")]
      public String Email { get; set; }

      [Display(Name = "Hobbies")]
      public IEnumerable<String> Hobbies { get; set; }

      [Display(Name = "Education")]
      public String Education { get; set; }
      
      // TODO: Add detailed address
   }
}