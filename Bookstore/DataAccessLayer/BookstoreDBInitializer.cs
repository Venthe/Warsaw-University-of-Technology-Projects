namespace Bookstore.DataAccessLayer
{
   using System;
   using System.Collections.Generic;
   using System.Data.Entity;
   using System.Data.Entity.Validation;
   using System.Diagnostics;
   using Bookstore.Models;

   public class BookstoreDBInitializer : DropCreateDatabaseIfModelChanges<BookstoreDBContext>
   {
      protected override void Seed(BookstoreDBContext context)
      {
         try
         {
            Debug.WriteLine("Seeding...");

            var hobbies = PrepareHobbies();
            context.Hobby.AddRange(hobbies);
            context.SaveChanges();

            var education = PrepareEducation();
            context.Education.AddRange(education);
            context.SaveChanges();

            var roles = PrepareRoles();
            context.Roles.AddRange(roles);
            context.SaveChanges();

            var users = PrepareUsers(education, roles, hobbies);
            context.Users.AddRange(users);
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

      private static IList<Education> PrepareEducation()
      {
         return new List<Education>
         {
            new Education { Code = "primary" },
            new Education { Code = "highschool" },
            new Education { Code = "university" }
         };
      }

      private static IList<Hobby> PrepareHobbies()
      {
         return new List<Hobby>
         {
            new Hobby { Code = "kayaking" },
            new Hobby { Code = "swimming" },
            new Hobby { Code = "dancing" },
            new Hobby { Code = "diving" },
            new Hobby { Code = "snorkeling" }
         };
      }

      private static IList<UserRole> PrepareRoles()
      {
         return new List<UserRole>
         {
            new UserRole{ RoleName = "admin"}
         };
      }

      private static IList<User> PrepareUsers(IList<Education> education, IList<UserRole> roles, IList<Hobby> hobbies)
      {
         IList<Address> address = new List<Address> {
               new Address { City = "Warsaw", FlatNumber = "5a", Country = "Poland", County = "Mazowsze", Street = "Krucza" },
               new Address { ApartamentNumber = "5", City = "Cracow", FlatNumber = "13", Country = "Poland", Street = "Wilcza" }
            };

         IList<User> admin = new List<User> {
               new User { Password = "aaaaaaaa", Username = "admin", Email = "admin@bookstore.temp", Name = "Andrzej", Surname = "Kowalski", Address = address[0], Education = education[2], Role = roles[0], Hobbies = new List<Hobby>{hobbies[1], hobbies[2] } },
               new User { Password = "aaaaaaaa", Username = "user", Email = "user@bookstore.temp", Name = "Wojciech", Surname = "Pietrzyński", Address = address[1], Education = education[1], Hobbies = new List<Hobby>{hobbies[0], hobbies[3] } }
            };
         return admin;
      }
   }
}