// chuji_box.c
inherit ITEM;
#include <ansi.h>
void create()
{
	set_name(HIM"�߼�����"NOR,({"box no3"}));
	set_weight(5000);
       
	if( clonep() )
		set_default_object(__FILE__);
	else
       {
	    set("long",
		"�����̵�����۵�"+this_object()->query("name")+",\nʹ��(openbox boxno3)"ZJURL("cmds:openbox box no3")ZJSIZE(22)"��"NOR"����!\n");
	    set("unit","��");
	    set("yuanbao", 10);
	    set("win_box",1);
	}
}
void init()
{
    if (environment()==this_player())
    add_action("do_openbox","openbox box no3",1);
}
//�򿪱���ĺ���
int do_openbox()
{
   int i;
   int num=1;
   string obj=""; 
   object ob;
 /*
   * �ƽ�,����ҩ,��ҩ,�˺���,�ǹ�,������װ,�ƴ�,����,�ؼ����,ǧ����
  */
   string *box=
({
"/clone/money/gold",
"/clone/suit/huashan/ling_boots","/clone/suit/huashan/ling_cloth","/clone/suit/huashan/ling_pants","/clone/suit/huashan/ling_sword",
"/clone/book/advance-blade","/clone/book/advance-club","/clone/book/advance-dagger","/clone/book/advance-dodge",
"/clone/book/advance-force","/clone/book/advance-parry","/clone/book/advance-staff",
"/clone/book/advance-sword","/clone/book/advance-throwing","/clone/book/advance-unarmed","/clone/book/advance-whip",
"/clone/book/lbook1","/clone/book/lbook2","/clone/book/lbook3","/clone/book/lbook4",
"/clone/money/gold",
"/clone/suit/huashan/ling_boots","/clone/suit/huashan/ling_cloth","/clone/suit/huashan/ling_pants","/clone/suit/huashan/ling_sword",
"/clone/book/advance-blade","/clone/book/advance-club","/clone/book/advance-dagger","/clone/book/advance-dodge",
"/clone/book/advance-force","/clone/book/advance-parry","/clone/book/advance-staff",
"/clone/book/advance-sword","/clone/book/advance-throwing","/clone/book/advance-unarmed","/clone/book/advance-whip",
"/clone/book/lbook1","/clone/book/lbook2","/clone/book/lbook3","/clone/book/lbook4",
"/clone/money/gold",
"/clone/suit/huashan/ling_boots","/clone/suit/huashan/ling_cloth","/clone/suit/huashan/ling_pants","/clone/suit/huashan/ling_sword",
"/clone/book/advance-blade","/clone/book/advance-club","/clone/book/advance-dagger","/clone/book/advance-dodge",
"/clone/book/advance-force","/clone/book/advance-parry","/clone/book/advance-staff",
"/clone/book/advance-sword","/clone/book/advance-throwing","/clone/book/advance-unarmed","/clone/book/advance-whip",
"/clone/book/lbook1","/clone/book/lbook2","/clone/book/lbook3","/clone/book/lbook4",
"/clone/money/gold",
"/clone/suit/huashan/ling_boots","/clone/suit/huashan/ling_cloth","/clone/suit/huashan/ling_pants","/clone/suit/huashan/ling_sword",
"/clone/book/advance-blade","/clone/book/advance-club","/clone/book/advance-dagger","/clone/book/advance-dodge",
"/clone/book/advance-force","/clone/book/advance-parry","/clone/book/advance-staff",
"/clone/book/advance-sword","/clone/book/advance-throwing","/clone/book/advance-unarmed","/clone/book/advance-whip",
"/clone/book/lbook1","/clone/book/lbook2","/clone/book/lbook3","/clone/book/lbook4",
"/clone/vip/putao",
"/clone/vip/unknowdan",
"/clone/vip/shenliwan",
"/clone/vip/xiandan",
"/clone/vip/xisuidan",
"/clone/vip/avipcard",
"/clone/book/mengzi",
});
  
	object me = this_player();
	if (me->is_busy())
	      { write("����һ������δ��ɣ�\n"); return 1;}
	if( me->is_fighting() )
	      { write("ս���п����䣿����ѽ��\n"); return 1;}
       
	message_vision(HIM"$N�������["+this_object()->query("name")+"]�ĸ���,���仯Ϊһ����ɫ�⻪��"NOR"\n",me);
	i=random((int)sizeof(box));
    
	ob = new(box[i]); 
   
    if(ob->query("base_value"))
    {
       num=random(5)+1;
       ob->set_amount(num);
    }
    
  tell_object(me,""HIM"*****************************************************\n");
  tell_object(me,""HIR"��ϲ"NOR"�����["+this_object()->query("name")+"]�еõ���..."+chinese_number(num)+ob->query("unit")+HIM+"<< "+ob->query("name")+HIM+" >>"+NOR+"\n");
 tell_object(me,""HIM"*****************************************************"NOR"\n");
    ob->move(me); 
    destruct(this_object());
	return 1;
}
int query_autoload()
{
	return 1;
}