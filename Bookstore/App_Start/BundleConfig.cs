﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Optimization;

namespace Bookstore.App_Start
{
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

         bundles.Add(new StyleBundle("~/Bookstore/css").Include("~/Content/Bookstore.css"));

         bundles.Add(new ScriptBundle("~/bundles/bookstore").Include("~/Scripts/bookstore.*"));
      }
   }
}