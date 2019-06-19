namespace Bookstore.Models
{
   using Microsoft.AspNet.Identity.EntityFramework;

   public class AppUser : IdentityUser
   {
      public virtual UserDetails UserDetails { get; set; }
   }
}