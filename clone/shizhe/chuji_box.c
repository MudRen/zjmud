// chuji_box.c
inherit ITEM;
#include <ansi.h>
void create()
{
	set_name(HIG"��������"NOR,({"box no1"}));
	set_weight(5000);
	set_max_encumbrance(8000);
	if( clonep() )
		set_default_object(__FILE__);
	else
	{
		set("long","����ϵͳ������"+this_object()->query("name")+",\nʹ��(openbox boxno1)"ZJURL("cmds:openbox boxno1")ZJSIZE(22)"��"NOR"����!\n");
		set("unit","��");
		set("yuanbao", 1);
		set("win_box",1);
	}
}
void init()
{
    if (environment()==this_player())
    add_action("do_openbox","openbox boxno1",1);
}
//�򿪱���ĺ���
int do_openbox()
{
   int i;
   int num=1;
   string obj=""; 
   object ob;
/*
    ͭǮ,����ҩ,��ҩ,�˺���,�ǹ�,������װ,�ƴ�,����,�����ڹ�,����ȭ��,���־�,���߰���
*/
   string *box=
({
"/clone/money/gold",
"/clone/food/jitui","/clone/food/jiudai",
"/clone/suit/new/new_sword","/clone/suit/new/new_blade","/clone/suit/new/new_cloth","/clone/suit/new/new_pants","/clone/suit/new/new_boots",
"/clone/book/basic-force","/clone/book/basic-unarmed","/clone/book/basic-dodge",
"/clone/book/lbook1","/clone/book/lbook2","/clone/book/lbook3","/clone/book/lbook4",
});
  
    object me = this_player();
	if (me->is_busy())
	      { write("����һ������δ��ɣ�\n"); return 1;}
	if( me->is_fighting() )
	      { write("ս���п����䣿����ѽ��\n"); return 1;}
       
    message_vision(HIW"$N�����["+this_object()->query("name")+HIW"]�ĸ���,���䷢��һ��ҫ�۵Ĺ⻪��"NOR"\n",me);

    i=random((int)sizeof(box));
    
    ob = new(box[i]); 
      if(ob->query("base_value"))
    {
       num=random(10)+1;
       ob->set_amount(num);
    }
  tell_object(me,""HIG"*****************************************************\n");
  tell_object(me,""HIR"��ϲ"NOR"�����["+this_object()->query("name")+"]�еõ���..."+chinese_number(num)+ob->query("unit")+HIG+"["+ob->query("name")+HIG"]"+NOR+"\n");
 	tell_object(me,""HIG"*****************************************************"NOR"\n");
    ob->move(me); 
    destruct(this_object());
	return 1;
}
int query_autoload()
{
	return 1;
}