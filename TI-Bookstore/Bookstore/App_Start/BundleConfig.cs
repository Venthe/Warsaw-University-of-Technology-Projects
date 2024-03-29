﻿namespace Bookstore.App_Start
{
   using System.Web.Optimization;

   public static class BundleConfig
   {
      public static void RegisterBundles(BundleCollection bundles)
      {
         bundles.Add(new ScriptBundle("~/bundles/jquery").Include(
                     "~/Scripts/jquery-{version}.js"));

         bundles.Add(new ScriptBundle("~/bundles/jqueryval").Include(
                     "~/Scripts/jquery.validate*"));

         bundles.Add(new ScriptBundle("~/bundles/bootstrap").Include(
                   "~/Scripts/bootstrap.js",
                   "~/Scripts/respond.js"));

         bundles.Add(new StyleBundle("~/Content/css").Include("~/Content/bootstrap.css"));

         bundles.Add(new StyleBundle("~/Bookstore/css").Include("~/BookstoreCss/bookstore.css"));

         bundles.Add(new ScriptBundle("~/Bookstore/js").Include("~/BookstoreJs/bookstore.*"));
      }
   }
}