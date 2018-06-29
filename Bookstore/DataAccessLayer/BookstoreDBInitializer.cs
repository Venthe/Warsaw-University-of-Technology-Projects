namespace Bookstore.DataAccessLayer
{
   using System;
   using System.Collections.Generic;
   using System.Data.Entity.Validation;
   using System.Diagnostics;
   using Bookstore.Models;

   public class BookstoreDBInitializer : System.Data.Entity.DropCreateDatabaseAlways<BookstoreDBContext>
   {
      protected override void Seed(BookstoreDBContext context)
      {
         try
         {
            Debug.WriteLine("Seeding...");
            IEnumerable<Hobby> hobbies = new List<Hobby>
         {
            new Hobby { Code = "kayaking" },
            new Hobby { Code = "swimming" },
            new Hobby { Code = "dancing" },
            new Hobby { Code = "diving" },
            new Hobby { Code = "snorkeling" }
         };
            context.Hobby.AddRange(hobbies);
            context.SaveChanges();
            IList<Education> education = new List<Education>
         {
            new Education { Code = "primary" },
            new Education { Code = "highschool" },
            new Education { Code = "university" }
         };
            context.Education.AddRange(education);
            context.SaveChanges();
            IList<UserRole> roles = new List<UserRole>
         {
            new UserRole{ RoleName = "admin"}
         };
            context.Roles.AddRange(roles);
            context.SaveChanges();

            var address = new Address { ApartamentNumber = "a", City = "a", FlatNumber = "a", Country = "a", County = "a", Street = "a" };
            var admin = new User { Password = "aaaaaaaa", Username = "admin", Email = "admin@admin.ad", Name = "Test", Surname = "Test2", Address = address, Education = education[0], Role = roles[0] };
            context.Users.Add(admin);
            context.SaveChanges();
         }
         catch (DbEntityValidationException e)
         {
            foreach (var eve in e.EntityValidationErrors)
            {
               Console.WriteLine($"Entity of type \"{eve.Entry.Entity.GetType().Name}\" in state \"{eve.Entry.State}\" has the following validation errors:");
               foreach (var ve in eve.ValidationErrors)
               {
                  Console.WriteLine($"- Property: \"{ve.PropertyName}\", Error: \"{ve.ErrorMessage}\"");
               }
            }

            throw;
         }
      }

      private static void InitializeUserRoles(BookstoreDBContext context)
      {
         IEnumerable<UserRole> roles = new List<UserRole>
         {
            new UserRole{ RoleName = "admin"}
         };

         context.Roles.AddRange(roles);

         context.SaveChanges();
      }

      private static void InitializeEducation(BookstoreDBContext context)
      {
         IEnumerable<Education> education = new List<Education>
         {
            new Education { Code = "primary" },
            new Education { Code = "highschool" },
            new Education { Code = "university" }
         };

         context.Education.AddRange(education);

         context.SaveChanges();
      }

      private static void InitializeHobbies(BookstoreDBContext context)
      {
         IEnumerable<Hobby> hobbies = new List<Hobby>
         {
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