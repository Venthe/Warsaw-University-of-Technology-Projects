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

      public bool IsLoggedIn(HttpResponseBase response) => GetCurrentUser(response) != null;

      public bool IsAdmin(HttpResponseBase response)
      {
         var currentUser = GetCurrentUser(response);

         if (currentUser == null) {
            return false;
         }

         return true;
      }

      public User GetCurrentUser(HttpResponseBase response)
      {
         var sessionKey = response.Cookies["BookstoreSession"]?["SessionKey"];
         if (sessionKey == null)
         {
            return null;
         }

         return (from s in dbContext.Session where s.Key.Equals(sessionKey) select s.User).Single();
      }
   }
}
