#include <ansi.h>

inherit ITEM; 

void create()
{
	set_name ("��ʦ���", ({ "master box"}));
	if( clonep() )
		set_default_object(__FILE__);
	else {
	set("long","����һ����̴ľ�Ƴɵĳ�ʦ��У��̺���һλʦ����ͽ�����еĹػ���"ZJURL("cmds:open master box")+ZJSIZE(20)+HIY"��"NOR"���ܹ���úܶ��������\n");
	set("unit","��");
	set_weight(100);
	set("value",10000);
      set("no_give",1);
      set("no_drop",1);
      set("no_get",1);
      set("no_sell",1);
	setup();
     }
}


void init()
{
	add_action("do_read","open");
  
}

int do_read(string arg)
{
	object me=this_player();
	object ob1;
	int i,k;
	    
	if (!arg)
      		return notify_fail("��Ҫ��ʲô��\n");
      		
	if (arg!="master box")
      		return notify_fail("��Ҫ��ʲô��У�\n");
      		
        message_vision(HIY"$N����һ��$n��
"HIW"$N�����һ��"HIG"����"HIW"��
$N�����һ��"HIG"����"HIW"��
$N�����һ��"HIG"����"HIW"��
$N������72Сʱ�Ļ�Աʱ��"HIW"��
$N�����һ����"HIY"�ƽ�"HIW"��"NOR"\n", me, this_object()); 	

                        ob1 = new("/clone/gift/putao");
                        ob1->move(me);
                        ob1 = new("/clone/gift/putao");
                        ob1->move(me);
                        ob1 = new("/clone/gift/putao");
                        ob1->move(me);

	        ob1 = new("/clone/money/gold");
		ob1->set_amount(100);
		ob1->move(me); 

	        me->add("zjvip/times",259200);
i=random(100);

if (i<25){
ob1 = new("/clone/gift/unknowdan");
ob1->move(me);
        message_vision(HIW"$N�����һ��"HIR"����ɵ�"HIW"��"NOR"\n", me, this_object());
//CHANNEL_D->do_channel(this_object(),"chat","��ϲ"HIM+me->query("name")+HIC"�����һ��"HIR"����ɵ�"NOR"��");
}
if (i>=25 && i<50){
ob1 = new("/clone/gift/shenliwan");
ob1->move(me);
        message_vision(HIW"$N�����һ��"HIG"������"HIW"��"NOR"\n", me, this_object());
//CHANNEL_D->do_channel(this_object(),"chat","��ϲ"HIM+me->query("name")+HIC"�����һ��"HIG"������"NOR"��");
}
if (i>=50 && i<75){
ob1 = new("/clone/gift/xiandan");
ob1->move(me);
        message_vision(HIW"$N�����һ��"HIY"�����ɵ�"HIW"��"NOR"\n", me, this_object());
//CHANNEL_D->do_channel(this_object(),"chat","��ϲ"HIM+me->query("name")+HIC"�����һ��"HIG"������"NOR"��");
}
if (i>=75 && i<98){
ob1 = new("/clone/gift/xisuidan");
ob1->move(me);
        message_vision(HIW"$N�����һ��"YEL"ϴ�赤"HIW"��"NOR"\n", me, this_object());
//CHANNEL_D->do_channel(this_object(),"chat","��ϲ"HIM+me->query("name")+HIC"�����һ��"YEL"ϴ�赤"NOR"��");
}
if (i>=98){
ob1 = new("/clone/gift/jiuzhuan");
ob1->move(me);
        message_vision(HIW"$N�����һ��"HIY"��ת��"HIW"��"NOR"\n", me, this_object());
//CHANNEL_D->do_channel(this_object(),"chat","��ϲ"HIM+me->query("name")+HIC"�����һ��"HIY"��ת��"NOR"��");
}




	destruct(this_object());
	return 1;
}	 

int query_autoload() { return 1; }