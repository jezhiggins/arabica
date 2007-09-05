/* $Id$
 *
 * 
 */

#ifndef ARABICA_ISTREAMHANDLE_H
#define ARABICA_ISTREAMHANDLE_H

#include <SAX/ArabicaConfig.hpp>
#include <cassert>
#include <iostream>
#include <memory>

// If we've been asked to debug, enforce post-conditions on all public API
// methods.  All post-conditions which do not relate to direct in-method
// assignment are tested.  (Those which relate to a direct assignment of a POD
// within the same method are not tested.)
#ifdef ARABICA_DEBUG
#define ISTREAMHANDLE_POSTCONDITION(x) assert(x)
#else
#define ISTREAMHANDLE_POSTCONDITION(x) do {} while (false)
#endif

namespace Arabica {
namespace SAX {

/** Reference-counting pointer to std::istream.
 *
 * \par Summary:
 * This works much like any other reference-counted pointer,
 * except that it only <i>optionally</i> owns the pointee.  That
 * is, it will not necessarily delete the pointee when the
 * reference count goes to zero.
 *
 * \par
 * Ownership of a std::istream is passed to an IStreamHandle via a
 * <code>std::auto_ptr<std::istream></code>.  Ownership of a
 * std::istream is passed between IStreamHandle by assignment.
 *
 * \see IStreamHandle(std::auto_ptr<std::istream>) for passing
 *      ownership at construction.
 * \see IStreamHandle::operator=(std::auto_ptr<std::istream>) for
 *      passing ownership after construction.
 * \see IStreamHandle(std::istream&) for constructing without
 *      passing ownership
 * \see IStreamHandle::operator=(std::istream&) for assigning
 *      without passing ownership.
 *
 * \par Justification:
 *
 * \par
 * This class is needed to fix an ownership problem between the
 * InputSource and EntityResovler classes.  InputSource is a SAX
 * class designed to wrap stream objects.  Normally, an
 * InputSource is constructed with reference to a std::istream
 * object.  There are two separate use-cases for InputSource which
 * lead to conflicting models of std::istream ownership.
 *
 * \par
 * -#   When an InputSource is constructed to pass to a parser
 *      <code>parse()</code> method, the InputSource is owned by
 *      the client code.  When <code>parse()</code> returns, the
 *      InputSource is no-longer needed and it's stream can be
 *      destroyed by the client code.  This will most likely
 *      happen when the variable goes out of scope).
 * -#   When an EntityResolver responds to a
 *      <code>resolveEntity()</code> request, it must return an
 *      InputSource.  In this case the InputSource, and more
 *      importantly, the std::istream, is needed by the parser for
 *      some time after <code>resolveEntity()</code> has returned.
 *
 * \par
 * In case 1, the std::istream in question may be local variable,
 * and so the InputSource simply cannot own it.
 *
 * \par
 * In case 2, the std::istream in question cannot be a local
 * variable because it must be returned from a method.  Since it
 * must be destroyed at some time known only to the parser, there
 * is no alternative but for the InputSource to own it.
 *
 * \par Solution:
 *
 * \par
 * To solve this issue, I have created the IStreamHandle and
 * modified InputSource.  IStreamHandle can behave either as a
 * std::istream* <i>or</i> as a reference-counting std::istream*.
 * The difference is in <i>ownership</i>:
 *
 * \par
 *      If an IStreamHandle is constructed with or assigned a
 *      std::auto_ptr<std::istream>, it <i>takes ownership</i> of
 *      the pointee.  If an IStreamHandle is constructed with or
 *      assigned a std::istream&, it <i>does not take
 *      ownership</i> of the pointee.
 *
 * \par
 *      Upon destruction or re-assignment, an IStreamHandle checks
 *      whether it is the last reference to its pointee, and
 *      whether it <i>owns</i> its pointee.  If both conditions
 *      are met, the IStreamHandle deletes its pointee.
 *
 * @author Philip Walford
 * \par Created:
 *      21/05/2003
 * 
 * 
 *
 *
 *
 * \internal
 * \par Pre- and Post-Conditions
 * All public API methods of IStreamHandle conform to the following
 * post-condition:
 * - <code>counter_</code> points to a valid heap-allocated integer greater
 *   than 0.
 *
 * \par
 * All public API methods of IStreamHandle that take an
 * auto_ptr<std::istream> parameter conform to the follow post-conditions.
 * For the purposes of these post-conditions, <code>rhs</code> will represent
 * the std::auto_ptr parameter.
 * - <code>is_</code> contains the value returned by <code>rhs.release()</code>.
 * - <code>rhs.get() == 0</code> (ownership has been transfered).
 * - <code>owner_ = true</code>
 * 
 * \par
 * All public API methods of IStreamHandle that take a std::istream&
 * parameter conform to the follow post-conditions.  For the purposes of
 * these post-conditions, <code>rhs</code> will represent the std::istream&
 * parameter.
 * - <code>is_ = &rhs</code>
 * - <code>owner_ = false</code>
 *
 * \par
 * The default constructor and release() methods of IStreamHandle conform to
 * the following post-conditions:
 * - <code>is_ = 0</code>
 * - <code>owner_ = false</code>
 *
 * \par
 * Further post-conditions are documented under the appropriate methods.
 */
class IStreamHandle
{
public:
    /** Create an IStreamHandle which does not point to any std::istream.
     *
     * \internal
     * \post is_ == 0
     * \post owner_ == false
     */
    IStreamHandle();

    /** Create an IStreamHandle which does not own it's std::istream.
     *
     * \par Ownership:
     * The IStreamHandle constructed in this manner does not own the
     * std::istream to which it points.
     *
     */
    IStreamHandle(std::istream& is);

    /** Create an IStreamHandle taking ownership of a std::istream.
     *
     * \par Ownership:
     * The IStreamHandle constructed in this manner owns the std::istream to
     * which <em>is</em> pointed.  This ownership may then be shared with
     * other IStreamHandle objects.
     *
     */
    explicit IStreamHandle(std::auto_ptr<std::istream> is);
    explicit IStreamHandle(std::auto_ptr<std::iostream> is);

    /** Construct an IStreamHandle sharing a std::istream with <em>rhs</em>.
     * 
     * \par Ownership
     * The IStreamHandle constructed in this manner will share ownership of
     * the std::istream to which it points if-and-only-if <em>rhs</em>
     * shares ownership of the std::istream.
     *
     * \internal
     * \post is_ == rhs.is_
     * \post counter_ == rhs.counter_
     * \post *counter_ == (<i>old value of</i> *(rhs.counter_)) + 1
     * \post owner_ == rhs.owner_
     */
    IStreamHandle(const IStreamHandle& rhs);

    /** Destroy an IStreamHandle, destroying the internal std::istream if
     * <code>this</code> <i>owns</i> the istream and is the last reference.
     *
     * \internal
     * \post is_ == 0
     * \post counter_ == 0
     * \post owner_ == false
     */
    ~IStreamHandle();

    /** Assign another IStreamHandle to <code>this</code>.  This destroys the
     * std::istream held by <code>this</code> if <code>this</code> <i>owns</i>
     * the istream and is the last reference.
     * 
     * \par Ownership:
     * After this operation, the IStreamHandle <code>this</code> will share
     * ownership of the std::istream to which it points if-and-only-if
     * <em>rhs</em> shares ownership of the std::istream.
     *
     * \internal
     * \post is_ == rhs.is_
     * \post counter_ == rhs.counter_
     * \post *counter_ == (<i>old value of</i> *(rhs.counter_)) + 1
     * \post owner_ == rhs.owner_
     */
    IStreamHandle& operator=(const IStreamHandle& rhs);

    /** Assign a new std::istream to <code>this</code>.  This destroys the
     * std::istream held by <code>this</code> if <code>this</code> <i>owns</i>
     * the istream and is the last reference.  Ownership of the istream is
     * transfered to <code>this</code>.
     *
     * \par Ownership:
     * After this operation, the IStreamHandle <code>this</code> owns the
     * std::istream to which <em>rhs</em> pointed.  This ownership may then be
     * shared with other IStreamHandle objects.
     *
     */
    IStreamHandle& operator=(std::auto_ptr<std::istream> rhs);
    IStreamHandle& operator=(std::auto_ptr<std::iostream> rhs);

    /** Assign a new std::istream to <code>this</code>.  This destroys the
     * std::istream held by <code>this</code> if <code>this</code> <i>owns</i>
     * the istream and is the last reference.
     *
     * \par Ownership:
     * After this operation, the IStreamHandle <code>this</code> does not own
     * the std::istream to which <em>rhs</em> points.
     *
     */
    IStreamHandle& operator=(std::istream& rhs);

    /** Return the std::istream contained by <code>this</code>. */
    std::istream* get() const;

    /** Release the std::istream held by <code>this</code>.  This will destroy
     * the internal std::istream if <code>this</code> <i>owns</i> the istream
     * and is the last reference.
     *
     * \internal
     * \post is_ == 0
     * \post owner_ == false
     */
    void release();

private:
    std::istream* is_;
    int*          counter_;
    bool          owner_;

    // Set the internal pointer and ownership
    // \post is_ == is
    // \post owner_ == own
    void set(std::istream* is, bool own);

    // Increment the counter.
    // \pre counter_ != 0
    // \post *counter_ = (<i>old value of</i> *counter_) + 1
    void addRef() const;

    // Decrement the counter and free memory if zero references remain and we
    // own the std::istream.  Clears internal pointers either way.
    // \post is_ == 0
    // \post counter_ == 0
    // \post owner_ = false
    void removeRef();
};

inline
IStreamHandle::IStreamHandle()
:   is_(0),
    counter_(new int(0)),
    owner_(false)
{
    addRef();
    ISTREAMHANDLE_POSTCONDITION(*counter_ == 1);
}

inline
IStreamHandle::IStreamHandle(std::istream& is)
:   is_(&is),
    counter_(new int(0)),
    owner_(false)
{
    addRef();
    ISTREAMHANDLE_POSTCONDITION(*counter_ == 1);
}

inline
IStreamHandle::IStreamHandle(std::auto_ptr<std::istream> is)
:   is_(is.release()),
    counter_(new int(0)),
    owner_(true)
{
    addRef();
    ISTREAMHANDLE_POSTCONDITION(*counter_ == 1);
    ISTREAMHANDLE_POSTCONDITION(is.get() == 0);
}

inline
IStreamHandle::IStreamHandle(std::auto_ptr<std::iostream> is)
:   is_(is.release()),
    counter_(new int(0)),
    owner_(true)
{
    addRef();
    ISTREAMHANDLE_POSTCONDITION(*counter_ == 1);
    ISTREAMHANDLE_POSTCONDITION(is.get() == 0);
}

inline
IStreamHandle::IStreamHandle(const IStreamHandle& rhs)
:   is_(rhs.is_),
    counter_(rhs.counter_),
    owner_(rhs.owner_)
{
    addRef();
    ISTREAMHANDLE_POSTCONDITION(*counter_ >= 2);
}

inline
IStreamHandle::~IStreamHandle()
{
    removeRef();
    ISTREAMHANDLE_POSTCONDITION(is_ == 0);
    ISTREAMHANDLE_POSTCONDITION(counter_ == 0);
    ISTREAMHANDLE_POSTCONDITION(owner_ == false);
}

inline
IStreamHandle& IStreamHandle::operator=(const IStreamHandle& rhs)
{
    // Add to rhs first to avoid self-assignment bug.
    rhs.addRef();
    removeRef();
    is_ = rhs.is_;
    counter_ = rhs.counter_;
    owner_ = rhs.owner_;

    ISTREAMHANDLE_POSTCONDITION(*counter_ >= 1);

    return *this;
}

inline
IStreamHandle& IStreamHandle::operator=(std::auto_ptr<std::istream> rhs)
{
    removeRef();
    set(rhs.release(), true);

    ISTREAMHANDLE_POSTCONDITION(*counter_ == 1);
    ISTREAMHANDLE_POSTCONDITION(owner_ == true);
    ISTREAMHANDLE_POSTCONDITION(rhs.get() == 0);

    return *this;
}

inline
IStreamHandle& IStreamHandle::operator=(std::auto_ptr<std::iostream> rhs)
{
    removeRef();
    set(rhs.release(), true);

    ISTREAMHANDLE_POSTCONDITION(*counter_ == 1);
    ISTREAMHANDLE_POSTCONDITION(owner_ == true);
    ISTREAMHANDLE_POSTCONDITION(rhs.get() == 0);

    return *this;
}

inline
IStreamHandle& IStreamHandle::operator=(std::istream& rhs)
{
    removeRef();
    set(&rhs, false);

    ISTREAMHANDLE_POSTCONDITION(*counter_ == 1);
    ISTREAMHANDLE_POSTCONDITION(owner_ == false);

    return *this;
}

inline
std::istream* IStreamHandle::get() const
{
    return is_;
}

inline
void IStreamHandle::set(std::istream* is, bool own)
{
    is_ = is;
    owner_ = own;
    counter_ = new int(0);
    addRef();
}

inline
void IStreamHandle::release()
{
    removeRef();
    // We're pretending to have a counted reference to 0, this ensures internal
    // consistency.
    set(0, false);
}

// Increment the counter.
inline
void IStreamHandle::addRef() const
{
    ++(*counter_);
    ISTREAMHANDLE_POSTCONDITION(*counter_ >= 1);
}

// Decrement the counter and free memory if zero references remain and we own
// the std::istream.  Clears internal pointers either way and resets counter_
// to a new int.
inline
void IStreamHandle::removeRef()
{
    // counter_ may be 0 if we are default-constructed or if someone has
    // called release().
    if (counter_)
    {
        if (--(*counter_) == 0)
        {
            if (owner_) 
            {
                delete is_;
            }
            delete counter_;
        }
    }
    is_      = 0;
    owner_   = false;
    counter_ = 0;
}

} // namespace SAX
} // namespace Arabica

#endif /* SAX_ISTREAMHANDLE_H */

