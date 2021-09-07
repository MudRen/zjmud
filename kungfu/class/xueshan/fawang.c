// /kungfu/class/xueshan/fawang.c  ���ַ���
// by secret

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;

#include <ansi.h>
#include "xueshan.h"

mixed ask_poli();
mixed ask_wulun();

void create()
{
	set_name("���ַ���", ({ "jinlun fawang", "fawang", "fawang" }));
	set("long",@LONG
����ѩɽ�µĻ��̷�������ѩɽ�µĵ�λ�������������Ħ�ǡ�
��һ���Ϻ����ģ�ͷ��ɮñ��
LONG
	);
	set("title", HIY "����" NOR);
	set("gender", "����");
	set("age", 50);
	set("attitude", "peaceful");
	set("shen_type", -1);

	set("str", 31);
	set("int", 32);
	set("con", 31);
	set("dex", 29);

	set("max_qi", 5200);
	set("max_jing", 5200);
	set("neili", 7500);
	set("max_neili", 7500);
	set("jiali", 100);
	set("combat_exp", 2400000);

	set_skill("force", 260);
	set_skill("longxiang", 260);
	set_skill("mizong-neigong", 260);
	set_skill("dodge", 210);
	set_skill("shenkong-xing", 210);
	set_skill("cuff", 240);
	set_skill("yujiamu-quan", 240);
	set_skill("hand", 250);
	set_skill("dashou-yin", 250);
	set_skill("parry", 250);
	set_skill("staff", 220);
	set_skill("xiangmo-chu", 220);
	set_skill("lamaism", 210);
	set_skill("literate", 200);
	set_skill("hammer", 270);
	set_skill("riyue-lun", 270);
	set_skill("sword", 250);
	set_skill("mingwang-jian", 250);

	map_skill("force", "longxiang");
	map_skill("dodge", "shenkong-xing");
	map_skill("cuff", "yujiamu-quan");
	map_skill("hand", "dashou-yin");
	map_skill("parry", "riyue-lun");
	map_skill("sword", "xiangmo-chu");
	map_skill("hammer", "riyue-lun");

	prepare_skill("hand", "dashou-yin");
	prepare_skill("cuff", "yujiamu-quan");

	create_family("ѩɽ��", 1, "���̷���");
	set("class", "bonze");

	set("inquiry", ([
		"����" : "����ѧϰ�������ַ��İ���ô��",
		"����" : "����ѧϰ�������ַ��İ���ô��",
		"����" : (: ask_poli :),
		"��������" : (: ask_wulun :),
		"�ܵ�" : "����ѩɽ�µ�ǰ�����˿�����һ��ȥ��ԭ���ܵ������������档",
		"�ص�" : "����ѩɽ�µ�ǰ�����˿�����һ��ȥ��ԭ���ܵ������������档",
	]));

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "hammer.poli" :),
		(: perform_action, "hammer.wulun" :),
		(: perform_action, "hand.jingang" :),
		(: perform_action, "cuff.chen" :),
		(: exert_function, "powerup" :),
		(: exert_function, "recover" :),
	}));

	set_temp("apply/attack", 150);
	set_temp("apply/defense", 150);
	set_temp("apply/damage", 100);
	set_temp("apply/unarmed_damage", 100);
	set_temp("apply/armor", 200);

	setup();

	carry_object("/d/xueshan/obj/jinlun")->wield();
	carry_object("/d/xueshan/obj/p-jiasha")->wear();
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
		command("say ��λ" + RANK_D->query_respect(ob) +
			"������ذɣ�");
		return;
	}

	if ((string)ob->query("family/family_name") != "ѩɽ��")
	{
		command("say ��λ" + RANK_D->query_respect(ob) +
			"�ȷǱ��µ��ӣ�������ذɣ�");
		return;
	}

	if ((int)ob->query_skill("lamaism", 1) < 100)
	{
		command("say ����ѩɽ�£���ϰ�����ķ�����Ҫ�ġ�");
		command("say ��λ" + RANK_D->query_respect(ob) +
			"�Ƿ�Ӧ�ö�����б��ŵ��ķ���");
		return;
	}

	command("smile");
	command("nod");
	command("say �������ѧϰ�𷨰ɣ�");
	command("recruit " + ob->query("id"));

	ob->set("title", HIY "���" NOR);
}

mixed ask_poli()
{
	object me;

	me = this_player();
	if (me->query("can_perform/riyue-lun/poli"))
		return "��������ʲô���ú�����ȥ��";

	if (me->query("family/family_name") != query("family/family_name"))
		return "����������ѩɽ����˵��";

	if (me->query_skill("riyue-lun", 1) < 120)
		return "��������ַ���Ϊ�����У��úõĸ�������";

	message_vision(HIY "$n" HIY "��$N" HIY "�������ֹ���"
		       "��˵��һЩ�ھ���"NOR"\n",
		       me, this_object());
	command("say ȥ�ɣ�");
	tell_object(me, HIG "��ͨ���������İ��"NOR"\n");
	if (me->can_improve_skill("hammer"))
		me->improve_skill("hammer", 90000);
	me->set("can_perform/riyue-lun/poli", 1);
	return 1;
}

mixed ask_wulun()
{
	object me;

	me = this_player();
	if (me->query("can_perform/riyue-lun/wulun"))
		return "����������ʲô���ú�����ȥ��";

	if (me->query("family/family_name") != query("family/family_name"))
		return "�����������ģ�";

	if (me->query_skill("riyue-lun", 1) < 120)
		return "��������ַ���Ϊ�����У�����������еİ��";

	message_vision(HIY "$n" HIY "��$N" HIY "�������ֹ���"
		       "��˵��һЩ�ھ���"NOR"\n",
		       me, this_object());
	command("say ȥ�ɣ�");
	tell_object(me, HIG "��ͨ�����������ҵİ��"NOR"\n");
	if (me->can_improve_skill("hammer"))
		me->improve_skill("hammer", 90000);
	me->set("can_perform/riyue-lun/wulun", 1);
	return 1;
}

void unconcious()
{
	die();
}
