namespace Bookstore.Services
{
   using System.Linq;
   using System.Web;
   using Bookstore.DataAccessLayer;
   using Bookstore.Models;

   public class AuthorizationService
   {
      private readonly BookstoreDBContext dbContext;

      public AuthorizationService() => dbContext = new BookstoreDBContext();

      public User GetCurrentUser(HttpRequestBase request)
      {
         var sessionKey = request.Cookies["BookstoreSession"]?["SessionKey"];
         if (sessionKey == null)
         {
            return null;
         }

         var users = from s in dbContext.Session where s.Key.Equals(sessionKey) select s.User;

         if (users.Count() != 1)
         {
            return null;
         }

         return users.Single();
      }

      public bool IsAdmin(HttpRequestBase request)
      {
         var currentUser = GetCurrentUser(request);

         if (currentUser == null)
         {
            return false;
         }

         var role = currentUser.Role?.RoleName.Equals("admin");

         return role != null;
      }

      public bool IsLoggedIn(HttpRequestBase request) => GetCurrentUser(request) != null;
   }
}
