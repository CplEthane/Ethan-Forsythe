using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Timers;
using System.Drawing;

namespace _2DGameEngine
{
    class npc
    {
        public enum Directions
        {
            right,
            left,
            up, 
            down
        };

        public int Map_X;
        public int Map_Y;

        public int Screen_X;
        public int Screen_Y;

        public int facingDirection;

        public Image facingForward1;
        public Image facingForward2;

        public Image facingBack1;
        public Image facingBack2;

        public Image facingRight1;
        public Image facingRight2;

        public Image facingLeft1;
        public Image facingLeft2;

        public Image currentFrame;


        public npc()
        {
            
        }

        
    }

    class merchant : npc
    {
        bool anim_iter;

        System.Timers.Timer merchantAnim = new System.Timers.Timer();

        public merchant()
        {
            anim_iter = false;

            merchantAnim.Elapsed += new ElapsedEventHandler(MerchantAnimationEvent);
            merchantAnim.Interval = 500;
            merchantAnim.Enabled = true;

            //facingRight1 = Image.FromFile("merchant_right_01.png");
            //facingRight2 = Image.FromFile("merchant_right_02.png");
        }

        public void activateMerchant()
        {

        }

        private void MerchantAnimationEvent(object source, ElapsedEventArgs e)
        {
            if (anim_iter == false)
            {
                if(facingDirection == (int)Directions.right)
                {
                    this.currentFrame = facingRight1;
                }
                anim_iter = true;
            }
            else if (anim_iter == true)
            {
                if (facingDirection == (int)Directions.right)
                {
                    this.currentFrame = facingRight2;
                }
                anim_iter = false;
            }
            else
            {
                anim_iter = false;
            }
        }
    }

    class roamingNPC : npc
    {
        public enum intendedDirection
        {
            east,
            west,
            north,
            south,
            idle
        };

        public bool CurrentDirectionEast;
        public bool CurrentDirectionWest;
        public bool CurrentDirectionSouth;
        public bool CurrentDirectionNorth;


        public bool IsCurrentlyMoving;
        private bool anim_iter;

        private int i;
        private int speed;
        private static Random rnd = new Random();
        private static int roamDelay = rnd.Next(1000, 3000);

        Point adjacentTestWest = new Point();
        Point adjacentTestEast = new Point();
        Point adjacentTestNorth = new Point();
        Point adjacentTestSouth = new Point();

        Point heroPoint = new Point();

        System.Timers.Timer npcAnim = new System.Timers.Timer();
        System.Timers.Timer npcWalk = new System.Timers.Timer();
        System.Timers.Timer npcMove = new System.Timers.Timer();

        public roamingNPC()
        {
            IsCurrentlyMoving = false;

            npcAnim.Elapsed += new ElapsedEventHandler(NPCAnimationEvent);
            npcAnim.Interval = 500;
            npcAnim.Enabled = true;

            npcWalk.Elapsed += new ElapsedEventHandler(NPCWalkEvent);
            npcWalk.Interval = roamDelay;
            npcWalk.Enabled = true;

            npcMove.Elapsed += new ElapsedEventHandler(NPCMoveEvent);
            npcMove.Interval = 17;
            npcMove.Enabled = true;

            anim_iter = false;
            CurrentDirectionEast = false;
            CurrentDirectionWest = false;
            CurrentDirectionNorth = false;
            CurrentDirectionSouth = false;
            i = 32;
            speed = 2;
            
            

        }

        private bool CanMove(int direction)
        {


            if (direction == (int)intendedDirection.east)
            {
                if (Hero.array[this.Map_Y, this.Map_X + 1] == 0)
                {
                    Hero.array[this.Map_Y, this.Map_X + 1] = 1;
                    return true;
                }
            }
            else if (direction == (int)intendedDirection.west)
            {
                if (Hero.array[this.Map_Y, this.Map_X - 1] == 0)
                {
                    Hero.array[this.Map_Y, this.Map_X - 1] = 1;
                    return true;
                }
            }
            else if (direction == (int)intendedDirection.north)
            {
                if (Hero.array[this.Map_Y - 1, this.Map_X] == 0)
                {
                    Hero.array[this.Map_Y - 1, this.Map_X] = 1;
                    return true;
                }
            }
            else if (direction == (int)intendedDirection.south)
            {
                if (Hero.array[this.Map_Y + 1, this.Map_X] == 0)
                {
                    Hero.array[this.Map_Y + 1, this.Map_X] = 1;
                    return true;
                }
            }
            else
            {
                direction = (int)intendedDirection.idle;
                return false;
            }
            return false;
        }

        

        public bool canTalk()
        {
            heroPoint.X = Hero.Map_X;
            heroPoint.Y = Hero.Map_Y;

            adjacentTestEast.X = this.Map_X+1;
            adjacentTestEast.Y = this.Map_Y;

            adjacentTestWest.X = this.Map_X - 1;
            adjacentTestWest.Y = this.Map_Y;

            adjacentTestNorth.X = this.Map_X;
            adjacentTestNorth.Y = this.Map_Y-1;

            adjacentTestSouth.X = this.Map_X;
            adjacentTestSouth.Y = this.Map_Y+1;

            if(adjacentTestEast == heroPoint && Hero.facing == 1)
            {
                return true;
            }
            else if (adjacentTestWest == heroPoint && Hero.facing ==0)
            {
                return true;
            }
            else if (adjacentTestNorth == heroPoint && Hero.facing == 3)
            {
                return true;
            }
            else if (adjacentTestSouth == heroPoint && Hero.facing == 2)
            {
                return true;
            }
            else
                return false;
        }

        private void NPCWalkEvent(object source, ElapsedEventArgs e)
        {
            int npcdirection = rnd.Next(0, 9);

            if (Form1.textbox_toggle)
                npcdirection = 5;


            if(CanMove(npcdirection) && !IsCurrentlyMoving)
            {
                
                IsCurrentlyMoving = true;
                    if (npcdirection == 0)
                    {
                        CurrentDirectionEast = true;
                    }
                    else if (npcdirection == 1)
                    {
                        CurrentDirectionWest = true;
                    }
                    else if (npcdirection == 2)
                    {
                        CurrentDirectionNorth = true;
                    }
                    else if (npcdirection == 3)
                    {
                        CurrentDirectionSouth = true;
                    }
                    else
                        IsCurrentlyMoving = false;
            }
        }

        private void NPCMoveEvent(object source, ElapsedEventArgs e)
        {
            if(IsCurrentlyMoving)
            {
                i -= speed;
                if(CurrentDirectionEast == true)
                {
                    this.Screen_X +=speed;
                }
                else if (CurrentDirectionWest == true)
                {
                    this.Screen_X -=speed;
                }
                else if (CurrentDirectionNorth == true)
                {
                    this.Screen_Y -=speed;
                }
                else if (CurrentDirectionSouth == true)
                {
                    this.Screen_Y +=speed;
                }
            }

            if(i==0)
            {
                IsCurrentlyMoving = false;
                Hero.array[this.Map_Y, this.Map_X] = 0;
                if (CurrentDirectionEast == true)
                {
                    
                    this.Map_X++;
                    CurrentDirectionEast = false;
                }
                else if (CurrentDirectionWest == true)
                {
                    this.Map_X--;
                    CurrentDirectionWest = false;
                }
                else if (CurrentDirectionNorth == true)
                {
                    this.Map_Y--;
                    CurrentDirectionNorth = false;
                }
                else if (CurrentDirectionSouth == true)
                {
                    this.Map_Y++;
                    CurrentDirectionSouth = false;
                }

                i = 32;
            }
        }

        private void NPCAnimationEvent(object source, ElapsedEventArgs e)
        {
            if (anim_iter == false)
            {
                //npcMale1.ChangeBmp("npcm2.png");
                Form1.malenpc = Image.FromFile("npcm2.png");

                anim_iter = true;
            }
            else if (anim_iter == true)
            {
                Form1.malenpc = Image.FromFile("npcm1.png");

                anim_iter = false;
            }
            else
            {
                anim_iter = false;
            }
        }
    }
}
