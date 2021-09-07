// /kungfu/class/xueshan/shanyong.c  ����
// by secret

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

#include <ansi.h>
#include "xuedao.h"

string ask_for_join();
int do_kneel();

void create()
{
	set_name("����", ({ "shan yong", "shan", "yong" }));
	set("long",@LONG
һ�����ֵ�����ɮ�ˣ����Ц�ݣ�ȴ����Ц��ص����¡�
LONG
	);
	set("title",HIR"Ѫ���ŵ���������"NOR);
	set("gender", "����");
	set("age", 35);
	set("attitude", "peaceful");
	set("shen_type", -1);
	set("str", 22);
	set("int", 21);
	set("con", 22);
	set("dex", 19);
	set("max_qi", 2800);
	set("max_jing", 1400);
	set("neili", 2600);
	set("max_neili", 2600);
	set("jiali", 15);
	set("combat_exp", 75000);

	set_skill("lamaism", 80);
	set_skill("literate", 60);
	set_skill("force", 80);
	set_skill("parry", 80);
	set_skill("blade", 80);
	set_skill("dodge", 80);
	set_skill("mizong-neigong", 80);
	set_skill("shenkong-xing", 80);
	set_skill("hand", 80);
	set_skill("dashou-yin", 80);
	set_skill("xue-dao", 80);

	map_skill("force", "mizong-neigong");
	map_skill("dodge", "shenkong-xing");
	map_skill("hand", "dashou-yin");
	map_skill("parry", "xue-dao");
	map_skill("blade", "xue-dao");

	set("inquiry",([
		"���"  : (: ask_for_join :),
		"����"  : (: ask_for_join :),
	]));

	create_family("Ѫ����", 6, "����");
	set("class", "bonze");

	setup();
	carry_object("/d/xueshan/obj/y-jiasha")->wear();
	carry_object("/clone/weapon/gangdao")->wield();
}

void init()
{
	add_action("do_kneel", "kneel");

}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob))
		return;

	if ((string)ob->query("gender") != "����")
	{
		command("say �Ҳ���Ůͽ�ܡ�\n");
		return;
	}
	if (ob->query("class") != "bonze")
	{
		ob->set_temp("pending/join_bonze", 1);
		command("say �㲻�ǳ����ˣ�����Ѫ�����ǲ��������ġ�"
			"��������Ҫ���ң��͹��°�(kneel)��");
		return;
	}
	command("recruit " + ob->query("id"));
}

string ask_for_join()
{
	object me;

	me = this_player();

	if( (string)me->query("class")=="bonze" )
		return "�����ӷ�����ͬ�ǳ����ˣ��ιʸ�ƶɮ�������Ц��\n";

	if( (string)me->query("gender") != "����" )
		return "ʩ��������������ǿ�ϲ�ɺأ���ϧ����ֻ����ͽ��\n";

	me->set_temp("pending/join_bonze", 1);
	return "�����ӷ����գ����գ�ʩ������������ҷ������(kneel)�ܽ䡣\n";
}

int do_kneel()
{
	object me = this_player();

	if (! me->query_temp("pending/join_bonze"))
		return notify_fail("����˰�㣬���û�����㡣\n");

	message_vision("$N˫�ֺ�ʮ�����������ع���������\n\n"
		       "$n������ƣ���$Nͷ�������Ħ���˼��£���$N��ͷ��������ȥ��\n\n",
		       me, this_object());

	command("smile");

	me->set("class", "bonze");
	command("recruit " + me->query("id"));

	return 1;
}
