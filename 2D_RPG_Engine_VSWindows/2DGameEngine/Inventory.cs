using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _2DGameEngine
{
    class Inventory
    {
    }

    class Weapon : Inventory
    {
        public enum weaponType
        {
            club,
            shortSword,
            magicSword
        };

        int[] value;

        public Weapon()
        {
            value[(int)weaponType.club] = 60;
            value[(int)weaponType.shortSword] = 600;            
        }
    }
}
