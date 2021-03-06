<?PHP
/**
 * This file is part of the ATK distribution on GitHub.
 * Detailed copyright and licensing information can be found
 * in the doc/COPYRIGHT and doc/LICENSE files which should be
 * included in the distribution.
 *
 * @package atk
 * @subpackage menu
 *
 * @copyright (c)2000-2004 Ibuildings.nl BV
 * @license http://www.achievo.org/atk/licensing ATK Open Source License
 *
 * @version $Revision: 6347 $
 * $Id$
 */
atkimport('atk.menu.atkplainmenu');

/**
 * Implementation of the Bootstrap menu.
 *
 * @author Michele Rota <michele.rota@me.com>
 * @package atk
 * @subpackage menu
 */
class atkBootstrapMenu extends atkPlainMenu
{

    /**
     * Render the menu
     * @return String HTML fragment containing the menu.
     */
    function render()
    {
        $page = & atkinstance("atk.ui.atkpage");
        $menu = $this->load();
        $page->addContent($menu);
        return $page->render("Menu", true);
    }

    /**
     * Get the menu
     *
     * @return string The menu
     */
    function getMenu()
    {
        return $this->load();
    }

    /**
     * Load the menu
     *
     * @return string The menu
     */
    function load()
    {
        global $g_menu;

        $menu = $this->parseItems($g_menu['main']);
        $ret = '<ul class="nav navbar-nav">';
        $ret .= $this->processMenu($menu);
        $ret .= '</ul>';
        return $ret;
    }

    private function processMenu($menu)
    {
        $ret = '';
        foreach ($menu as $item) {
            if ($this->isEnabled($item)) {
                $hasSubmenu = isset($item['submenu']) && count($item['submenu']);
                $ret .= '<li' . ($hasSubmenu ? ' class="dropdown"' : '') . '>';
                $url = $item['url'] ? $item['url'] : '#';
                $attrs = $hasSubmenu ? 'class="dropdown-toggle" data-toggle="dropdown" role="button" aria-expanded="false"' : '';
                $ret .= '<a href="' . $url . '" ' . $attrs . '>' . atk_htmlentities($this->getMenuTranslation($item['name'], $item['module']));
                if ($hasSubmenu) {
                    $ret .= '<span class="caret"></span></a>';
                    $ret .= '<ul class="dropdown-menu" role="menu">' . $this->processMenu($item['submenu']) . '</ul>';
                } else {
                    $ret .= '</a>';
                }
                $ret .= '</li>';
            }
        }
        return $ret;
    }


    private function parseItems(&$items)
    {
        foreach ($items as &$item) {
            $this->parseItem($item);
        }
        return $items;
    }

    private function parseItem(&$item)
    {
        global $g_menu;
        if ($item['enable'] && array_key_exists($item['name'], $g_menu)) {
            $item['submenu'] = $this->parseItems($g_menu[$item['name']]);
            return $item;
        }
    }

}