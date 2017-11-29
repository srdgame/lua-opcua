#pragma once

#define REG_ENUM(NAME) module.new_enum<NAME>(#NAME, {
#define ENUM(NAME, ID) { #ID, NAME::ID },
#define ENUM_RENAME(NAME, NID, ID) { #NID, NAME::ID },
#define ENUM_END(NAME, ID) { #ID, NAME::ID } });
#define ENUM_END_RENAME(NAME, NID, ID) { #NID, NAME::ID } });

