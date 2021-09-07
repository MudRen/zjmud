// tufei.c

inherit NPC;
#include <ansi.h>
#include "/d/fuben/npc/fb_skill.h"

//�ɱ�����Ʒ�б�
string *random_ob = ({
    "/clone/vip/putao",
    "/clone/money/gold",
});

void create()
{
	set_name(HIR"����"NOR, ({ "han fei", "fei", }) );
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
	ob = this_object();
	::init();

	if (userp(me)) {
		command("say �Ҵ����ҵĵ��̣��ٺ�~~��������������\n");
		
		//npc�Ѷ��ǲ��ø��������߿�ѧ���ܵȼ�����
		if (!this_object()->query_temp("do_clone"))
			ob->do_clone(me, 20);
		if (!random(3))
			ob->do_clone(me, 20);
		kill_ob(me);
		me->kill_ob(this_object());
	}
}
void die()
{
	string id = random_ob[random(sizeof(random_ob))];//�����Ʒ
	object ob;
	
	switch (random(10))
	{
		case 0 : 
		case 5 :
		case 9 :
                  ob = new(id);
                  if (ob->query("id")=="gold")
                      ob->set_amount(1 + random(5));
                  ob->move(this_object());
/*
                  if (ob->quer_amount())
                      ob->set_amount(1 + random(5));
                  ob->move(this_object());
			new(id)->move(this_object());
*/
		break;
	}
	::die();
}
