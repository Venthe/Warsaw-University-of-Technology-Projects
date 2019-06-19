namespace Bookstore.Models
{
   using Microsoft.AspNet.Identity.EntityFramework;

   public class AppRole : IdentityRole
   {
      public AppRole()
      {
      }

      public AppRole(string name)
         : base(name)
      {
      }
   }
}