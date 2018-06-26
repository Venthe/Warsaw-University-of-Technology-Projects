using Bookstore.Models;
using System;
using System.Collections.Generic;
using System.Data.Entity;
using System.Diagnostics;
using System.Linq;
using System.Web;

namespace Bookstore.DataAccessLayer
{
   public class BookstoreDBInitializer : System.Data.Entity.DropCreateDatabaseIfModelChanges<BookstoreDBContext>
   {
      protected override void Seed(BookstoreDBContext context)
      {
         base.InitializeDatabase(context);

         Debug.WriteLine("Seeding...");
         InitializeHobbies(context);
         InitializeEducation(context);
      }

      private static void InitializeEducation(BookstoreDBContext context)
      {
         IEnumerable<Education> education = new List<Education>() {
            new Education { Code = "primary" },
            new Education { Code = "highschool" },
            new Education { Code = "university" }
         };

         context.Education.AddRange(education);

         context.SaveChanges();
      }

      private static void InitializeHobbies(BookstoreDBContext context)
      {
         IEnumerable<Hobby> hobbies = new List<Hobby>() {
            new Hobby { Code = "kayaking" },
            new Hobby { Code = "swimming" },
            new Hobby { Code = "dancing" },
            new Hobby { Code = "diving" },
            new Hobby { Code = "snorkeling" }
         };

         context.Hobby.AddRange(hobbies);

         context.SaveChanges();
      }
   }
}