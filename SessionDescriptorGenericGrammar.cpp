/**
 * This file is part of WebP2P.
 *
 * WebP2P is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * WebP2P is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with WebP2P.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Filename:    SessionDescriptorGenericGrammar.cpp
 * Author(s):   Dries Staelens
 * Copyright:   Copyright (c) 2010 Dries Staelens
 * Description: Implementation for the RFC 4566 SDP grammar rules.
 * See:         http://tools.ietf.org/html/rfc4566
**/

/* WebP2P includes */
#include "SessionDescriptorGenericGrammar.hpp"

SessionDescriptorGenericGrammar::SessionDescriptorGenericGrammar() {
    using           boost::spirit::qi::iso8859_1::char_;
    using namespace boost::spirit::qi::iso8859_1;
    using namespace boost::spirit::qi;

    /* generic sub-rules: addressing */
    unicast_address      = IP4_address | IP6_address | FQDN | extn_addr;
    multicast_address    = IP4_multicast | IP6_multicast | FQDN | extn_addr;
    IP4_multicast        = m1 
                        >> char_('.') >> decimal_uchar
                        >> char_('.') >> decimal_uchar
                        >> char_('.') >> decimal_uchar
                        >> char_('/') >> ttl >> -(char_('/') >> integer);
                        // IPv4 multicast addresses may be in the
                        // range 224.0.0.0 to 239.255.255.255
    m1                   = (char_('2') >> char_('2') >> char_('4', '9'))
                         | (char_('2') >> char_('3') >> abnf.DIGIT);
    IP6_multicast        = hexpart >> -(char_('/') >> integer);
                        // IPv6 address starting  with FF
    bm                   = (char_('2') >> char_('2') >> char_('0', '4'))
                         | (char_('2') >> char_('1') >> abnf.DIGIT)
                         | (char_('2') >> char_('0') >> abnf.DIGIT)
                         | (char_('1') >> abnf.DIGIT >> abnf.DIGIT)
                         | (POS_DIGIT >> abnf.DIGIT)
                         | abnf.DIGIT;
    ttl                  = (POS_DIGIT >> repeat(0, 2)[abnf.DIGIT]) 
                         | char_('0');
    FQDN                 = repeat(4, inf)[alpha_numeric 
                                                 | char_('-') | char_('.')];
                        // fully qualified domain name as specified
                        // in RFC 1035 (and updates)
    IP4_address          = b1
                         >> char_('.') >> decimal_uchar
                         >> char_('.') >> decimal_uchar
                         >> char_('.') >> decimal_uchar;
    b1                   = decimal_uchar.alias();
                        // less than "224"

    /* The following is consistent with RFC 2373, Appendix B. */
    IP6_address          = hexpart >> -(char_(':') >> IP4_address);
    hexpart              = (hexseq  >> char_(':') >> char_(':') >> -hexseq)
                         | (char_(':') >> char_(':') >> -hexseq)
                         | hexseq;
    hexseq               = hex4 >> *(lit(':') >> hex4);
    hex4                 = repeat(1,4)[abnf.HEXDIG];

    /* generic for other address families */
    extn_addr            = non_ws_string.alias();

    /* generic sub-rules: datatypes */
    text                 = byte_string.alias();
                        // default is to interpret this as UTF8 text.
                        // ISO 8859-1 requires "a=charset:ISO-8859-1"
                        // session-level attribute to be used
    byte_string          = +(!(byte_('\x00') | byte_('\x0A') | byte_('\x0D'))
                        >> byte_);
    non_ws_string        = +(abnf.VCHAR | char_('\x80', '\xFF'));
                        // string of visible characters
    token_char           = char_('\x21') 
                         | char_('\x23', '\x27') 
                         | char_('\x2A', '\x2B')
                         | char_('\x2D', '\x2E')
                         | char_('\x30', '\x39')
                         | char_('\x41', '\x5A')
                         | char_('\x5E', '\x7E');
    token                = +(token_char);
    email_safe           = !(byte_('\x00')
                         | byte_('\x0A')
                         | byte_('\x0D')
                         | byte_('\x28')
                         | byte_('\x29')
                         | byte_('\x3C')
                         | byte_('\x3E'))
                        >> byte_;
                        // any byte except NUL, CR, LF, or the quoting
                        // characters ()<>
    integer              = POS_DIGIT >> *abnf.DIGIT;

    /* generic sub-rules: primitives */
    alpha_numeric        = abnf.ALPHA | abnf.DIGIT;
    POS_DIGIT            = byte_('\x31') 
                         | byte_('\x32')
                         | byte_('\x33')
                         | byte_('\x34')
                         | byte_('\x35')
                         | byte_('\x36')
                         | byte_('\x37')
                         | byte_('\x38')
                         | byte_('\x39');
    decimal_uchar        = (char_('2') >> char_('5') >> char_('0', '5'))
                         | (char_('2') >> char_('0', '4') >> abnf.DIGIT)
                         | (char_('1') >> abnf.DIGIT >> abnf.DIGIT)
                         | (POS_DIGIT >> abnf.DIGIT)
                         | abnf.DIGIT;

    unicast_address.name("unicast-address");
    multicast_address.name("multicast-address");
    IP4_multicast.name("IP4-multicast");
    m1.name("m1");
    IP6_multicast.name("IP6-multicast");
    bm.name("bm");
    ttl.name("ttl");
    FQDN.name("FQDN");
    IP4_address.name("IP4-address");
    b1.name("b1");
    IP6_address.name("IP6-address");
    hexpart.name("hexpart");
    hexseq.name("hexseq");
    hex4.name("hex4");
    extn_addr.name("extn-addr");
    text.name("text");
    byte_string.name("byte-string");
    non_ws_string.name("non-ws-string");
    token_char.name("token-char");
    token.name("token");
    email_safe.name("email-safe");
    integer.name("integer");
    alpha_numeric.name("alpha-numeric");
    POS_DIGIT.name("POS-DIGIT");
    decimal_uchar.name("decimal-uchar");
}