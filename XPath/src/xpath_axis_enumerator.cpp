#include <XPath/impl/xpath_axis_enumerator.hpp>

using namespace Arabica::XPath;

const AxisEnumerator::NamedAxis AxisEnumerator::AxisLookupTable[] = { 
              { ANCESTOR,           AxisEnumerator::CreateAxis<AxisEnumerator::AncestorAxisWalker> },
              { ANCESTOR_OR_SELF,   AxisEnumerator::CreateAxis<AxisEnumerator::AncestorOrSelfAxisWalker> },
              { ATTRIBUTE,          AxisEnumerator::CreateAxis<AxisEnumerator::AttributeAxisWalker> },
              { CHILD,              AxisEnumerator::CreateAxis<AxisEnumerator::ChildAxisWalker> },
              { DESCENDANT,         AxisEnumerator::CreateAxis<AxisEnumerator::DescendantAxisWalker> },
              { DESCENDANT_OR_SELF, AxisEnumerator::CreateAxis<AxisEnumerator::DescendantOrSelfAxisWalker> },
              { FOLLOWING,          AxisEnumerator::CreateAxis<AxisEnumerator::FollowingAxisWalker> },
              { FOLLOWING_SIBLING,  AxisEnumerator::CreateAxis<AxisEnumerator::FollowingSiblingAxisWalker> },
              { NAMESPACE,          AxisEnumerator::CreateAxis<AxisEnumerator::NamespaceAxisWalker> },
              { PARENT,             AxisEnumerator::CreateAxis<AxisEnumerator::ParentAxisWalker> },
              { PRECEDING,          AxisEnumerator::CreateAxis<AxisEnumerator::PrecedingAxisWalker> },
              { PRECEDING_SIBLING,  AxisEnumerator::CreateAxis<AxisEnumerator::PrecedingSiblingAxisWalker> },
              { SELF,               AxisEnumerator::CreateAxis<AxisEnumerator::SelfAxisWalker> },
              { static_cast<Axis>(0), 0 } 
            };
