using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace Bookstore.Models
{
   public class UserViewModel
   {
      public User User { get; set; }
      public ICollection<Education> Education { get; set; }
      public ICollection<Hobby> Hobby { get; set; }
   }
}