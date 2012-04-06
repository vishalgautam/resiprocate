#if defined(HAVE_CONFIG_H)
#include "config.h"
#endif

#include "resip/stack/PlainContents.hxx"
#include "resip/stack/SipMessage.hxx"
#include "rutil/Logger.hxx"
#include "rutil/ParseBuffer.hxx"
#include "rutil/WinLeakCheck.hxx"

using namespace resip;
using namespace std;

#define RESIPROCATE_SUBSYSTEM Subsystem::SIP

const PlainContents PlainContents::Empty;
static bool invokePlainContentsInit = PlainContents::init();


bool
PlainContents::init()
{
   static ContentsFactory<PlainContents> factory;
   (void)factory;
   return true;
}


PlainContents::PlainContents()
   : Contents(getStaticType()),
     mText()
{}

PlainContents::PlainContents(const Data& txt)
   : Contents(getStaticType()),
     mText(txt)
{}

PlainContents::PlainContents(const HeaderFieldValue& hfv, const Mime& contentsType)
   : Contents(hfv, contentsType),
     mText()
{
}
 
PlainContents::PlainContents(const Data& txt, const Mime& contentsType)
   : Contents(contentsType),
     mText(txt)
{
}

PlainContents::PlainContents(const PlainContents& rhs)
   : Contents(rhs),
     mText(rhs.mText)
{
}

PlainContents::~PlainContents()
{
}

PlainContents&
PlainContents::operator=(const PlainContents& rhs)
{
   if (this != &rhs)
   {
      Contents::operator=(rhs);
      mText = rhs.mText;
   }
   return *this;
}

Contents* 
PlainContents::clone() const
{
   return new PlainContents(*this);
}

const Mime& 
PlainContents::getStaticType() 
{
   static Mime type("text","plain");
   return type;
}

EncodeStream& 
PlainContents::encodeParsed(EncodeStream& str) const
{
   //DebugLog(<< "PlainContents::encodeParsed " << mText);
   str << mText;
   return str;
}

void 
PlainContents::parse(ParseBuffer& pb)
{
   //DebugLog(<< "PlainContents::parse: " << pb.position());

   const char* anchor = pb.position();
   pb.skipToEnd();
   pb.data(mText, anchor);

   //DebugLog("PlainContents::parsed <" << mText << ">" );
}


/* ====================================================================
 * The Vovida Software License, Version 1.0 
 * 
 * Copyright (c) 2000 Vovida Networks, Inc.  All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 
 * 3. The names "VOCAL", "Vovida Open Communication Application Library",
 *    and "Vovida Open Communication Application Library (VOCAL)" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact vocal@vovida.org.
 *
 * 4. Products derived from this software may not be called "VOCAL", nor
 *    may "VOCAL" appear in their name, without prior written
 *    permission of Vovida Networks, Inc.
 * 
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND
 * NON-INFRINGEMENT ARE DISCLAIMED.  IN NO EVENT SHALL VOVIDA
 * NETWORKS, INC. OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT DAMAGES
 * IN EXCESS OF $1,000, NOR FOR ANY INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 * 
 * ====================================================================
 * 
 * This software consists of voluntary contributions made by Vovida
 * Networks, Inc. and many individuals on behalf of Vovida Networks,
 * Inc.  For more information on Vovida Networks, Inc., please see
 * <http://www.vovida.org/>.
 *
 */
