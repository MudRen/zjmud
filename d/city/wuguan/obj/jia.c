
#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(HIW "������" NOR, ({ "bingqi jia", "jia" }) );         
        set_weight(30000000);
        if( clonep() )
                set_default_object(__FILE__);
        else{
        set("unit", "��");
        set("long", "����һ��ר�������Ÿ��ֱ����ļ��ӡ�
�����У�
       ��(bian)��        ��(dao)�� 
       ��(gun)��         ��(bang)��
       ��(gangzhang)��   ��(jian)��
       ��(chui)��        ��(ling)�� 

���������ߡ�\n
�����ʽ: na <��������> from jia \n");
        set("material","wood");
        set("no_get",1);
        }
        setup();
}
/*
void init()
{
       add_action("do_get","na");
}

int do_get(string arg)
{
       object me,ob;
       string arg1,arg2;
       me=this_player();
       if(!arg || sscanf(arg, "%s from %s", arg1, arg2)!=2)
            return notify_fail("�����ʽ: na <��������> from jia��\n");
       if (arg2!="jia")
            return notify_fail("�����ʽ: na <��������> from jia��\n");
       if(me->query_temp("marks/��"))
            return notify_fail("���Ѿ��ù��ˡ�\n");
//     if(present(arg1, me) || present(arg1, environment()))
//          return notify_fail("�Ѿ������������ˡ�\n");
       switch (arg1){
          case "jian": ob=new("/clone/weapon/changjian"); break;             
          case "dao": ob=new("/clone/weapon/blade"); break;   
          case "bian": ob=new("/clone/weapon/whip"); break;         
          case "ling": ob=new("/clone/weapon/tieling"); break;
          case "gangzhang": ob=new("/clone/weapon/gangzhang"); break;
          case "gun": ob=new("clone/weapon/tiegun"); break;           
          case "chui": ob=new("clone/weapon/tiechui"); break;
          case "bang": ob=new("clone/weapon/zhubang"); break; 
          default :
                 return notify_fail("û�����ֱ�����\n");
       }
       if(ob){
       	 ob->set("value", 10);
       	 ob->move(me);
       }
       message_vision("$N�ӱ��������ó�һ��$n��\n",me, ob); 
       me->set_temp("marks/��",1);
       return 1;
}
*/