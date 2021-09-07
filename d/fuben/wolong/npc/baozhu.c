// tufei.c

inherit NPC;
#include <ansi.h>
#include "/d/fuben/npc/fb_skill.h"

mixed ask_yinguo();

//�ɱ�����Ʒ�б�
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
	set_name(HIR"��Х��"NOR, ({ "zhou xiaotian"}) );
	set("gender", "����");
	set("age", 45);
	set("long", "����������������ˡ�\n");

	set("combat_exp", 1000000+random(3000000));

	set("attitude", "peaceful");
	set("str", 30);
	set("int", 30);
	set("con", 30);
	set("dex", 30);
	
	set("inquiry", ([
		"���": (: ask_yinguo :),
	]) );

	set_basic();
	setup();

	add_money("gold", 1+random(10));
}

void init(object me)
{
	object ob;
	me = this_player();
	ob = this_object();
	::init();

	if (userp(me)&&!me->query_temp("zxt_again")) {
		
		//npc�Ѷ��ǲ��ø��������߿�ѧ���ܵȼ�����
		if (!this_object()->query_temp("do_clone"))
			ob->do_clone(me, 100);
		if (!random(3))
			ob->do_clone(me, 100);
		command("say �Ҵ����ҵ�����������~~���Һ�˵���𣡣�\n");
		kill_ob(me);
		me->kill_ob(this_object());
	}
}

mixed ask_yinguo()
{
	int exp,gold;
	object me,ob;

	ob = this_object();
	me = this_player();

	if(me->is_fighting(ob)||!me->query_temp("zxt_again"))
	{
		command("say �ϻ���˵���������˵����\n");
		kill_ob(me);
		me->kill_ob(this_object());
		return 1;
	}
	tell_object(me,"��Х�쿪ʼ������ϸ��˵��������¡�����\n");
	tell_object(me,"ԭ����Х���������ʱ��һζ�ؿ�����𣬽������������ң�������һλ�����˾��뷨����������֣�
���������һö���������������ʿǰ��̽�أ��Դﵽ�赶ɱ�˵�Ŀ�ġ�
���ˣ����������ס��㲻����Ц���á�
���������Ź���Х�죬�뿪��������\n");


	exp = ob->query_skill("force",1)*6;
	me->add("combat_exp",exp);
      gold=1+random(10);
      me->add("balance",gold*10000);
	tell_object(me,ZJOBLONG+ZJBR+ZJBR"���´������������"+exp+"�㾭���"+gold+"���ƽ�"ZJBR+ZJBR"\n");
	destruct(ob);
	return 1;
}

void die()
{
	string id = random_ob[random(sizeof(random_ob))];//�����Ʒ
	object me,killer,ob;
	int exp;

	me = this_object();

	if (objectp(killer = query_last_damage_from()))
	{
		if(!killer->query_temp("zxt_again"))
		{
			me->remove_killer(killer);
			killer->remove_killer(me);
			killer->set_temp("zxt_again",1);
			tell_object(killer,"����������Х��ɱ����ȴ����Ƴ�������ϵ��������ƣ���������"+RANK_D->query_respect(killer)+"���������飡���ұ�˵���䡣\n");
			tell_object(killer,"���ǲ������ֱ��ɱ����Х�죬������ǰѯ��һ�£�\n");
			tell_object(killer,ZJSIZE(20)+ZJURL("cmds:kill zhouxiaotian")+"ֱ��ɱ��"NOR"    "+ZJSIZE(20)+
					ZJURL("cmds:ask zhou xiaotian about ���")+"��ǰѯ��"NOR"\n");
			ob = new(base_name(me));
			ob->move(environment(me));
			destruct(me);
			return;
		}
		exp = this_object()->query_skill("force",1)*6;
		killer->add("combat_exp",exp);
		tell_object(killer,ZJOBLONG+ZJBR+ZJBR"���´���������ɱ����"+name()+"�����"+exp+"�㾭�顣"ZJBR+ZJBR"\n");
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
