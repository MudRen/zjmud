//huangyi.c

inherit NPC;

#include <ansi.h>

void create()
{
	set_name(HIY "����" NOR, ({ "huang yi" }) );
	set("title", CYN "Ⱥ��˽�" NOR);
	set("gender", "Ů��" );
	set("age", 22);
	set("str", 30);
	set("per", 40);
	set("long", @LONG
һ��ȫ�����´��Ż�װ����¶���ص���Ů��
LONG
	);
	set("combat_exp", 10);
	set("attitude", "friendly");
	setup();
	set("chat_chance", 15);
	set("chat_msg", ({
		"����˵������˵�������ӣ���ʹ��˰ɣ�������������ʲô���õģ��Ժõģ����õģ�Ҫʲô��ʲô��\n",
		"����̾���������Ѿ�Ȱ����Ѿͷ�����ˣ��������춼ĥ���ˣ������ǲ���ȥ�ӿͣ�\n",
		"���¶�����˵������͹ԹԶ������ҵĻ��ɣ���ָ����˭���������ȥ�ˣ�\n",
	}) );

	setup();
	carry_object(__DIR__"obj/skirt")->wear();
}

int accept_fight(object me)
{
	command("say СŮ�����������Ķ��֣�");
	return 0;
}

int accept_kill(object me)
{       
	object ob;
	if (is_fighting()) return 1;
	if (query("called")) return 1;
	command("say Ҫɱ���ˣ������˾�������");
	ob = present("bao biao");
	if (! ob)
	{
		seteuid(getuid());
		ob=new(__DIR__"baobiao");
		ob->move(environment());
	}
	message_vision(HIC "\n��Ȼ�����������������ڣ���$N"
		       HIC "��һ������ʲô����������£���"
		       "������"NOR"\n", me);
	ob->kill_ob(me);
	ob->set_leader(me);
	me->kill_ob(ob);
	set("called", 1);
	call_out("regenerate", 200);
	return 0;
}

int regenerate()
{
	set("called", 0);
	return 1;
}
