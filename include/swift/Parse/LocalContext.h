//===--- LocalContext.h - Parser state across a local context ---*- C++ -*-===//
//
// This source file is part of the Swift.org open source project
//
// Copyright (c) 2014 - 2017 Apple Inc. and the Swift project authors
// Licensed under Apache License v2.0 with Runtime Library Exception
//
// See https://swift.org/LICENSE.txt for license information
// See https://swift.org/CONTRIBUTORS.txt for the list of Swift project authors
//
//===----------------------------------------------------------------------===//
//
// This file defines the LocalContext class, which holds state
// required by the parser for parsing statements and expressions.
//
//===----------------------------------------------------------------------===//

#ifndef SWIFT_PARSE_LOCALCONTEXT_H
#define SWIFT_PARSE_LOCALCONTEXT_H

#include "llvm/ADT/DenseMap.h"
#include "swift/AST/Identifier.h"
#include <cassert>

namespace swift {
  class Identifier;

/// Information associated with parsing a local context.
class LocalContext {
  /// A map holding the next discriminator for declarations with
  /// various identifiers.
  llvm::DenseMap<Identifier, unsigned> LocalDiscriminators;

  LocalContext(const LocalContext &) = delete;
  LocalContext &operator=(const LocalContext &) = delete;

public:
  LocalContext() = default;

  /// Return a number that'll be unique in this context across all
  /// declarations with the given name.
  unsigned claimNextNamedDiscriminator(Identifier name) {
    assert(!name.empty() &&
           "setting a local discriminator on an anonymous decl; "
           "maybe the name hasn't been set yet?");
    return LocalDiscriminators[name]++;
  }
};

/// Information associated with parsing the top-level context.
class TopLevelContext : public LocalContext {};

} // end namespace swift

#endif
