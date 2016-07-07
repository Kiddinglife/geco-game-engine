/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _LOG4CXX_HELPERS_OBJECT_IMPL_H
#define _LOG4CXX_HELPERS_OBJECT_IMPL_H

#include <log4cxx/helpers/object.h>

namespace log4cxx
{
   namespace helpers
   {
      /** Implementation class for Object.*/
	   class LOG4CXX_EXPORT ObjectImpl : public virtual Object
	   {
	   public:
		   ObjectImpl();
		   virtual ~ObjectImpl();
		   void addRef() const;
		   void releaseRef() const;

		   // added for VS2015
		   #if _MSC_VER >= 1900
		   ObjectImpl(ObjectImpl && o)
		   {
			   ref = o.ref;
			   o.ref = 0;
		   }

		   ObjectImpl& operator=(ObjectImpl && o)
		   {
			   ref = o.ref;
			   o.ref = 0;

			   return *this;
		   }
		   #endif
		   // -----

	   protected:
		   mutable unsigned int volatile ref;

	   private:
		   //
		   //   prevent object copy and assignment
		   //
		   ObjectImpl(const ObjectImpl&);
		   ObjectImpl& operator=(const ObjectImpl&);
	   };
   }
}

#endif //_LOG4CXX_HELPERS_OBJECT_IMPL_H
