// tufei.c

inherit NPC;
#include <ansi.h>
#include "/d/fuben/npc/fb_skill.h"

//ɱͷ��ɱ�����Ʒ�б�
string *random_ob = ({
    "/clone/gift/tianxiang1",
    "/clone/vip/putao",
    "/clone/vip/putao",
    "/clone/vip/lingzhi2",
    "/clone/money/gold",
    "/clone/money/gold",
    "/clone/money/gold",
});

void create()
{
	set_name("��ͷ", ({ "jiaotou", }) );
	set("gender", "����");
	set("age", 35);
	set("long", "��һ���������һ�������ɷ��ģ��������������η��\n");

	set("combat_exp", 1000000+random(3000000));

	set("attitude", "peaceful");
	set("str", 20);
	set("int", 20);
	set("con", 20);
	set("dex", 20);
	
	set_basic();
	setup();

	add_money("gold", 1+random(3));
}
void init(object me)
{
	object ob;
	me = this_player();
	ob=this_object();
	::init();

	if (userp(me)) {
		command("say С�ӣ��е㱾�°�����������㣡\n");
		
		//npc�Ѷ��ǲ��ø��������߿�ѧ���ܵȼ�����
		if (!this_object()->query_temp("do_clone"))
			ob->do_clone(me, 40);
		if (!random(3))
			ob->do_clone(me, 40);
		kill_ob(me);
		me->kill_ob(this_object());
	}
}
void die()
{
	string id = random_ob[random(sizeof(random_ob))];//�����Ʒ
	object killer,ob;
	int exp;

	if (objectp(killer = query_last_damage_from()))
	{
		exp = this_object()->query_skill("force",1)*4;
		killer->add("combat_exp",exp);
		tell_object(killer,ZJOBLONG+ZJBR+ZJBR"��ɱ��"+name()+"�����"+exp+"�㾭�顣"ZJBR+ZJBR"\n");
	}
	
	switch (random(10))
	{
		case 0 : 
		case 5 :
		case 9 :
			new(id)->move(this_object());
		break;
	}
	::die();
}
