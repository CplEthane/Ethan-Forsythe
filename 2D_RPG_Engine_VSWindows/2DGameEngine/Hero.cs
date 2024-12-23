using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Timers;
using System.Drawing;

namespace _2DGameEngine
{
    public class Hero
    {


        public enum intendedDirection
        {
            east,
            west,
            north,
            south
        };

        static public int facing;

        private bool anim_iter;
        public bool isMoving;

        static public int Map_X;
        static public int Map_Y;

        static public int[,] array;

        System.Timers.Timer heroAnim = new System.Timers.Timer();

        public Hero()
        {
            heroAnim.Elapsed += new ElapsedEventHandler(heroAnimationEvent);
            heroAnim.Interval = 500;
            heroAnim.Enabled = true;

            Map_X = 16;
            Map_Y = 23;
            isMoving = false;
            array = Town1.southhomeArray;
            anim_iter = false;
        }

        

        public bool CanMove(int direction)
        {
            if (Form1.textbox_toggle)
                return false;

            if(direction == (int)intendedDirection.east)
            {
                if (array[Map_Y, Map_X + 1] == 0)
                {
                    array[Map_Y, Map_X + 1] = 1;
                    return true;
                }
                else if (array[Map_Y, Map_X + 1] > 1)
                    return true;
            }
            else if (direction == (int)intendedDirection.west)
            {
                if (array[Map_Y, Map_X-1] == 0)
                {
                    array[Map_Y, Map_X - 1] = 1;
                    return true;
                }
                else if (array[Map_Y, Map_X - 1] > 1)
                    return true;
            }
            else if (direction == (int)intendedDirection.north)
            {
                if (array[Map_Y-1, Map_X] == 0)
                {
                    array[Map_Y - 1, Map_X] = 1;
                    return true;
                }
                else if (array[Map_Y-1, Map_X] > 1)
                    return true;
            }
            else if (direction == (int)intendedDirection.south)
            {
                if (array[Map_Y+1, Map_X] == 0)
                {
                    array[Map_Y + 1, Map_X] = 1;
                    return true;
                }
                else if (array[Map_Y+1, Map_X] > 1)
                    return true;
            }
            return false;
        }

        public void heroAnimationEvent(object source, ElapsedEventArgs e)
        {
            if (anim_iter == false)
            {
                if(facing == (int)intendedDirection.east)
                    Form1.heroCurrentFrame = Form1.heroRight1;
                else if (facing == (int)intendedDirection.west)
                    Form1.heroCurrentFrame = Form1.heroLeft1;
                else if (facing == (int)intendedDirection.north)
                    Form1.heroCurrentFrame = Form1.heroBack1;
                else if (facing == (int)intendedDirection.south)
                    Form1.heroCurrentFrame = Form1.heroFront1;

                anim_iter = true;
            }
            else if (anim_iter == true)
            {
                if (facing == (int)intendedDirection.east)
                    Form1.heroCurrentFrame = Form1.heroRight2;
                else if (facing == (int)intendedDirection.west)
                    Form1.heroCurrentFrame = Form1.heroLeft2;
                else if (facing == (int)intendedDirection.north)
                    Form1.heroCurrentFrame = Form1.heroBack2;
                else if (facing == (int)intendedDirection.south)
                    Form1.heroCurrentFrame = Form1.heroFront2;


                anim_iter = false;
            }
            else
            {
                anim_iter = false;
            }
        }
    }
    
}
