#include <ansi.h>

inherit NPC;
inherit F_MASTER;

mixed ask_me(); 
#include "gaibang.h"

void consider();

void create()
{
	set_name("���Ԫ", ({"ma dayuan", "ma", "dayuan"}));
	set("title", "ؤ�︱����");
	set("gender", "����");
	set("age", 45);
	set("long", 
		"һ����ʮ����ĺ��ӣ�������ؤ�︱�������Ԫ��\n");
	set("attitude", "peaceful");
	set("str", 35);
	set("int", 21);
	set("con", 32);
	set("dex", 25);

	set("qi", 3500);
	set("max_qi", 3500);
	set("jing", 1800);
	set("max_jing", 1800);
	set("neili", 4800);
	set("max_neili", 4800);
	set("jiali", 120);
	
	set("combat_exp", 2000000);
	set("shen_type", 1);
	set("score", 25000);
	
	set_skill("force", 200);
	set_skill("huntian-qigong", 200);
	set_skill("jiaohua-neigong", 180);
	set_skill("unarmed", 180);
	set_skill("changquan", 180);
	set_skill("claw", 200);
	set_skill("suohou-gong", 200);
	set_skill("dodge", 180);
	set_skill("feiyan-zoubi", 180);
	set_skill("parry", 200);
	set_skill("begging", 180);
	set_skill("checking", 180);

	set("no_teach", ([
		"huntian-qigong" : "Ҫѧ���������Ұ��������˼�ȥ��",
	]));

	map_skill("force", "huntian-qigong");
	map_skill("unarmed", "jueming-tui");
	map_skill("claw", "suohou-gong");
	map_skill("parry", "suohou-gong");
	map_skill("dodge", "feiyan-zoubi");

	prepare_skill("claw", "suohou-gong");

	set("inquiry", ([
		"����": (: ask_me :),
	]));

	create_family("ؤ��", 17, "������");

	set("chat_chance_combat", 80);
	set("chat_msg_combat", ({
		(: perform_action, "claw.suo" :),
		(: exert_function, "recover" :),
	}) );

	setup();
}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob)) return;

	if (ob->query("beggarlvl") < 8)
	{
		command("say ���ڱ���ĵ�λ̫�ͣ����������λ����ѧϰ�ɣ�");
		return;
	}

	if ((int)ob->query_str() < 26)
	{
		command("say ����ؤ�������һ���Ը���Ϊ����" + 
		RANK_D->query_respect(ob) + "�������У��ƺ�����ѧؤ��Ĺ���");
		return;
	}

	if (ob->query_skill("force") < 150)
	{
		command("say ����ڹ���򻹲��У��Ⱥͱ��ʦ��ѧϰ�ɡ�");
		return;
	}

	command("say �ðɣ�ϣ��" + RANK_D->query_respect(ob) +
		"�ܺú�ѧϰ�����书�������ڽ����д���һ����Ϊ��");

	command("recruit " + ob->query("id"));
	if((string)ob->query("class") != "beggar")
		ob->set("class", "beggar");
}

mixed ask_me()
{
	object me;

	me = this_player();
	if (me->query("can_perform/suohou-gong/suo"))
		return "�Լ���ȥ��ϰ�������Ǿ�������ģ�";

	if (me->query("family/family_name") != query("family/family_name"))
		return RANK_D->query_respect(me) + "�ֲ������ǰ�ģ���������";

	if (me->query("beggarlvl") < 9)
		return "�ҵ������Ĵ�����һЩ�����������ǵ����Ϊ�Ŵ�����֮����¡�";

	if (me->query_skill("suohou-gong", 1) < 150)
		return "��������������ң�Ҫ��������";

	message_vision( HIY "$n" HIY "Ц��Ц��������$N"
			HIY "���ߵ����Ը��˼��䣬ȫ����"
			"���ľ�΢Ҫ�裬$N" HIY "һ����"
			"һ�߲�ס�ص�ͷ��"NOR"\n",
			me, this_object());
	command("nod");
	command("say �����������Ҫ�����ڣ��ɼ�����ˣ�");
	tell_object(me, HIC "��ѧ���ˡ�������һ�С�"NOR"\n");
	if (me->can_improve_skill("claw"))
		me->improve_skill("claw", 160000);
	me->set("can_perform/suohou-gong/suo", 1);
	return 1;
}

