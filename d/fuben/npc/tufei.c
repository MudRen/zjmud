// tufei.c

inherit NPC;
//#include <fb_skill.h>
#include "/d/fuben/npc/fb_skill.h"

void create()
{
	set_name("����", ({ "tu fei", "tufei", "bandit","fei" }) );
	set("gender", "����");
	set("age", 30);
	set("long", "��һ��������⪬һ�������ɷ��ģ��������������η��\n");

	set("combat_exp", 100000+random(300000));
	
	set("attitude", "peaceful");
	set("str", 20);
	set("int", 20);
	set("con", 20);
	set("dex", 20);
	set_basic();
	setup();

	add_money("silver", 50+random(50));
}
void init(object me)
{
	object ob;
	me = this_player();
	ob=this_object();
	::init();
	
	if (userp(me)) {
		command("say ʲô�ˣ���Ȼ�ҵ��ڷ�կ����Ұ��\n");
		//npc�Ѷ��ǲ��ø��������߿�ѧ���ܵȼ�����
		if (!this_object()->query_temp("do_clone"))
			ob->do_clone(me, 1);
		if (!random(3))
			ob->do_clone(me, 1);
		kill_ob(me);
		me->kill_ob(this_object());
	}
}
