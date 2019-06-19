namespace Bookstore.Models
{
   using System.Collections.Generic;

   public class UserViewModel
   {
      public User User { get; set; }

      public ICollection<Education> Education { get; set; }

      public ICollection<Hobby> Hobby { get; set; }
   }
}