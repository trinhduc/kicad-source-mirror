/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2015 Jean-Pierre Charras, jp.charras at wanadoo.fr
 * Copyright (C) 2004-2017 KiCad Developers, see change_log.txt for contributors.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you may find one here:
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 * or you may search the http://www.gnu.org website for the version 2 license,
 * or you may write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

/*
 * @file sch_marker.h
 * @brief SCH_MARKER class definition.
 */

#ifndef TYPE_SCH_MARKER_H_
#define TYPE_SCH_MARKER_H_

#include <sch_item_struct.h>
#include <marker_base.h>


/* Names for corresponding types of markers: */
extern const wxChar* NameMarqueurType[];


class SCH_MARKER : public SCH_ITEM, public MARKER_BASE
{
public:
    SCH_MARKER();

    SCH_MARKER( const wxPoint& aPos, const wxString& aText );

    // Do not create a copy constructor.  The one generated by the compiler is adequate.

    wxString GetClass() const override
    {
        return wxT( "SCH_MARKER" );
    }

    void ViewGetLayers( int aLayers[], int& aCount ) const override;

    void Draw( EDA_DRAW_PANEL* aPanel, wxDC* aDC, const wxPoint& aOffset,
               GR_DRAWMODE aDraw_mode, COLOR4D aColor = COLOR4D::UNSPECIFIED ) override;

    void Plot( PLOTTER* aPlotter ) override
    {
        // SCH_MARKERs should not be plotted. However, SCH_ITEM will fail an
        // assertion if we do not confirm this by locally implementing a no-op
        // Plot().
        (void) aPlotter;
    }

    EDA_RECT const GetBoundingBox() const override;

    // Geometric transforms (used in block operations):

    void Move( const wxPoint& aMoveVector ) override
    {
        m_Pos += aMoveVector;
    }


    void MirrorY( int aYaxis_position ) override;

    void MirrorX( int aXaxis_position ) override;

    void Rotate( wxPoint aPosition ) override;

    /**
     * Compare DRC marker main and auxiliary text against search string.
     *
     * @param aSearchData - Criteria to search against.
     * @param aAuxData A pointer to optional data required for the search or NULL
     *                 if not used.
     * @param aFindLocation - a wxPoint where to put the location of matched item. can be NULL.
     * @return True if the DRC main or auxiliary text matches the search criteria.
     */
    bool Matches( wxFindReplaceData& aSearchData, void* aAuxData, wxPoint* aFindLocation ) override;

    void GetMsgPanelInfo( EDA_UNITS_T aUnits, std::vector< MSG_PANEL_ITEM >& aList ) override;

    bool IsSelectStateChanged( const wxRect& aRect ) override;

    wxString GetSelectMenuText( EDA_UNITS_T aUnits ) const override
    {
        return wxString( _( "ERC Marker" ) );
    }

    BITMAP_DEF GetMenuImage() const override;

    wxPoint GetPosition() const override { return m_Pos; }

    void SetPosition( const wxPoint& aPosition ) override { m_Pos = aPosition; }

    bool HitTest( const wxPoint& aPosition, int aAccuracy ) const override;

    EDA_ITEM* Clone() const override;

#if defined(DEBUG)
    void Show( int nestLevel, std::ostream& os ) const override;
#endif
};

#endif // TYPE_SCH_MARKER_H_
