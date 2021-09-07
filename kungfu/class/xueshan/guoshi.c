// /kungfu/class/xueshan/guoshi.c  ���Ʋֹ�ʦ
inherit NPC;
inherit F_MASTER;

#include <ansi.h>
#include "xueshan.h"

string ask_for_join();

void create()
{
	set_name("���Ʋֹ�ʦ", ({ "gongtangcang guoshi", "guoshi" }));
	set("long",@LONG
���Ʋֹ�ʦ��ѩɽ���е�λ�ϸߵ����Ϊ������𷨣��˴����ص�
ǰ����ԭ��̳���ڡ�
LONG
	);
	set("title", HIY "������" NOR);
	set("nickname", HIG "��ʦ" NOR);
	set("gender", "����");
	set("age", 40);
	set("attitude", "peaceful");
	set("shen_type", -1);
	set("str", 24);
	set("int", 28);
	set("con", 26);
	set("dex", 25);

	set("max_qi", 1500);
	set("max_jing", 500);
	set("neili", 1500);
	set("max_neili", 1500);
	set("jiali", 20);
	set("combat_exp", 120000);

	set_skill("literate", 50);
	set_skill("force", 100);
	set_skill("mizong-neigong", 100);
	set_skill("dodge", 100);
	set_skill("shenkong-xing", 80);
	set_skill("parry", 70);
	set_skill("staff", 80);
	set_skill("xiangmo-chu", 80 );
	set_skill("sword",50);
	set_skill("mingwang-jian",40);
	set_skill("cuff", 90);
	set_skill("yujiamu-quan", 80);
	set_skill("hand", 90);
	set_skill("dashou-yin", 90);

	map_skill("force", "mizong-neigong");
	map_skill("dodge", "shenkong-xing");
	map_skill("cuff", "yujiamu-quan");
	map_skill("parry", "xiangmo-chu");
	map_skill("staff", "xiangmo-chu");
	map_skill("sword", "mingwang-jian");

	prepare_skill("cuff", "yujiamu-quan");
	prepare_skill("hand", "dashou-yin");

	// ����ѧϰ�ļ���
	set_skill("literate", 200);
	set_skill("sanscrit", 200);
	set_skill("lamaism",  200);
	set_skill("buddhism", 200);

	create_family("ѩɽ��", 4, "������");
	set("class", "bonze");

	set("inquiry",([
		"����"  : (: ask_for_join :),
	]));

	setup();

	carry_object("/d/shaolin/obj/chanzhang")->wield();
	carry_object("/d/xueshan/obj/c-jiasha")->wear();
	carry_object("/d/xueshan/obj/sengmao")->wear();
}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob))
		return;
 
	if ((string)ob->query("gender") != "����")
	{
		command("say ��ϰ�����ڹ���Ҫ����֮�塣");
		command("say ��λ" + RANK_D->query_respect(ob) +
			"������ذɣ�");
		return;
	}

	if ((string)ob->query("class") != "bonze")
	{
		command("say �ҷ��ŵ����������ࡣ");
		ob->set_temp("pending/join_bonze", 1);
		command("say ʩ������������ҷ���"ZJURL("cmds:kneel")+ZJSIZE(15)"����"NOR"(kneel)�ܽ䡣\n");
		return;
	}

	if ((string)ob->query("family/family_name") != "ѩɽ��")
	{
		command("say ��λ" + RANK_D->query_respect(ob) +
			"�ȷǱ��µ��ӣ�������ذɣ�");
		return;
	}

	if ((int)ob->query_skill("lamaism", 1) < 40)
	{
		command("say ����ѩɽ�£���ϰ�����ķ�����Ҫ�ġ�");
		command("say ��λ" + RANK_D->query_respect(ob) +
			"�Ƿ�Ӧ�ö�����б��ŵ��ķ���");
		return;
	}

	command("say �ã��ʹ���һЩ�书�ɣ�");
	command("recruit " + ob->query("id"));

	ob->set("title",HIY "����" NOR);
}

void init()
{
	add_action("do_kneel", "kneel");
	add_action("do_say", "say");
}

string ask_for_join()
{
	object me;

	me = this_player();

	if ((string)me->query("class") == "bonze")
		return "�����ӷ� ���Ѿ��ǳ������ˣ��ιʸ�ƶɮ�������Ц��\n";

	if ((string)me->query("gender") != "����")
		return "ʩ��������������ǿ�ϲ�ɺأ���ϧ����ֻ����ͽ��\n";

	me->set_temp("pending/join_bonze", 1);

	return "�����ӷ����գ����գ�ʩ�����������"
	       "�ҷ���"ZJURL("cmds:kneel")+ZJSIZE(15)"����"NOR"(kneel)�ܽ䡣\n";
}

int do_kneel()
{
	object me = this_player();

	if (! me->query_temp("pending/join_bonze"))
		return 0;

	message_vision("$N˫�ֺ�ʮ�����������ع���������\n\n"
		       "$n������ƣ���$Nͷ�������Ħ���˼��£���"
		       "$N��ͷ��������ȥ��\n\n", me, this_object());

	me->set("class", "bonze");
	me->set("title",HIY "����" NOR);      

	command("smile");
	command("say �ã��ʹ���һЩ�书�ɣ�");
	command("recruit " + me->query("id"));

	return 1;
}

int do_say(string arg)
{

	object me = this_player();

	if (! arg || arg == "") return 0;

	if (arg == "���ֳ�ת")
	{
		me->move("/d/xueshan/guangchang");
		return 1;
	}
}

void unconcious()
{
	die();
}

int recognize_apprentice(object me, string skill)
{
	if (me->query("shen") > 0)
	{
		command("say ����ҷ���Ե���ҿ���ܲ�˳�ۣ����ǿ�Щ���ɣ�");
		return -1;
	}

	if (skill != "lamaism" && skill != "literate" && skill != "sanscrit" && skill != "buddhism")
	{
		command("say ��Щ���������ʦ��ѧ�ɣ���ֻ�ܴ���һЩ֪ʶ���㡣");
		return -1;
	}

	return 1;
}