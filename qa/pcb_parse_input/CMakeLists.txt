# This program source code file is part of KiCad, a free EDA CAD application.
#
# Copyright (C) 2018 KiCad Developers, see CHANGELOG.TXT for contributors.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, you may find one here:
# http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
# or you may search the http://www.gnu.org website for the version 2 license,
# or you may write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA


if( BUILD_GITHUB_PLUGIN )
    set( GITHUB_PLUGIN_LIBRARIES github_plugin )
endif()

add_dependencies( pnsrouter pcbcommon pcad2kicadpcb ${GITHUB_PLUGIN_LIBRARIES} )

add_executable( qa_pcb_parse_input
    # This is needed for the global mock objects
    ../qa_utils/mocks.cpp

    main.cpp

  ../../common/base_units.cpp
  ../../common/xnode.cpp
  ../../common/base_screen.cpp
)

include_directories( BEFORE ${INC_BEFORE} )
include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/polygon
    ${CMAKE_SOURCE_DIR}/pcbnew
    ${CMAKE_SOURCE_DIR}/common
    ${CMAKE_SOURCE_DIR}/pcbnew/router
    ${CMAKE_SOURCE_DIR}/pcbnew/tools
    ${CMAKE_SOURCE_DIR}/pcbnew/dialogs
    ${Boost_INCLUDE_DIR}
    ${INC_AFTER}
)

target_link_libraries( qa_pcb_parse_input
    pcbcommon
    legacy_wx
    polygon
    pnsrouter
    common
    pcbcommon
    bitmaps
    polygon
    pnsrouter
    common
    pcbcommon
    bitmaps
    polygon
    pnsrouter
    common
    pcbcommon
    bitmaps
    polygon
    pnsrouter
    common
    pcbcommon
    3d-viewer
    bitmaps
    gal
    pcad2kicadpcb
    common
    pcbcommon
    ${GITHUB_PLUGIN_LIBRARIES}
    qa_utils
    ${wxWidgets_LIBRARIES}
)

# we need to pretend to be something to appease the units code
target_compile_definitions( qa_pcb_parse_input
    PRIVATE PCBNEW
)