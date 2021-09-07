// Npc: /kungfu/class/shaolin/da-mo.c
// Date: YZC 96/01/19

inherit NPC;
inherit F_MASTER;

#include <ansi.h>
#include "shaolin.h"

mixed ask_qingxin();
mixed ask_luan();
mixed ask_shang();
mixed ask_zhe();

void create()
{
	set_name("��Ħ����", ({
		"da mo",
		"da",
		"mo",
	}));
	set("long",
		"����һλ���������������ɮ����һϮ���ݽ�˿������ġ�\n"
		"��ȴ�����⣬Ŀ�̴�Ц���������飬һ�ɵõ���ɮ���ơ�\n"
		"�����������ɿ�ɽ���桢�������ֵ�������ɮ��Ħ��ʦ��\n"
	);

	set("title", HIR"���ֿ�ɽ��ʦ"NOR);
	set("gender", "����");
	set("attitude", "friendly");
	set("class", "bonze");

	set("age", 300);
	set("shen_type", 1);

	set("str", 40);
	set("int", 50);
	set("con", 45);
	set("dex", 40);

	set("max_qi", 8000);
	set("max_jing", 4000);
	set("neili", 9000);
	set("max_neili", 9000);
	set("jiali", 50);
	set("combat_exp", 10000000);

	set_skill("buddhism", 800);
	set_skill("literate", 350);

	set_skill("blade", 320);
	set_skill("claw", 320);
	set_skill("club", 320);
	set_skill("cuff", 320);
	set_skill("dodge", 320);
	set_skill("finger", 320);
	set_skill("force", 400);
	set_skill("hand", 320);
	set_skill("parry", 320);
	set_skill("staff", 320);
	set_skill("strike", 320);
	set_skill("sword", 320);
	set_skill("whip", 320);
	set_skill("medical", 300);
	set_skill("shaolin-yishu", 300);

	set_skill("banruo-zhang", 320);
	set_skill("cibei-dao", 320);
	set_skill("damo-jian", 320);
	set_skill("fengyun-shou", 320);
	set_skill("fumo-jian", 320);
	set_skill("hunyuan-yiqi", 320);
	set_skill("shaolin-xinfa", 320);
	set_skill("jingang-quan", 320);
	set_skill("longzhua-gong", 320);
	set_skill("luohan-quan", 320);
	set_skill("nianhua-zhi", 320);
	set_skill("pudu-zhang", 320);
	set_skill("qianye-shou", 320);
	set_skill("sanhua-zhang", 320);
	set_skill("riyue-bian", 320);
	set_skill("shaolin-shenfa", 320);
	set_skill("weituo-gun", 320);
	set_skill("wuchang-zhang", 320);
	set_skill("xiuluo-dao", 320);
	set_skill("yingzhua-gong", 320);
	set_skill("yijinjing", 400);
	set_skill("yizhi-chan", 320);
	set_skill("zui-gun", 320);
	set_skill("sanscrit", 300);

	map_skill("blade", "cibei-dao");
	map_skill("claw", "longzhua-gong");
	map_skill("club", "wuchang-zhang");
	map_skill("cuff", "luohan-quan");
	map_skill("dodge", "shaolin-shenfa");
	map_skill("finger", "nianhua-zhi");
	map_skill("force", "yijinjing");
	map_skill("hand", "fengyun-shou");
	map_skill("parry", "nianhua-zhi");
	map_skill("staff", "weituo-gun");
	map_skill("strike", "sanhua-zhang");
	map_skill("sword", "fumo-jian");
	map_skill("whip", "riyue-bian");

	prepare_skill("finger", "nianhua-zhi");
	prepare_skill("strike", "sanhua-zhang");

	set("inquiry", ([
		"����"   : "����ѧʲô���У�",
		"����"   : "����ѧʲô������",
		"��Ħ���Ľ�": (: ask_qingxin :),
		"���Ľ�"    : (: ask_qingxin :),
		"��Ħ������": (: ask_luan :),
		"������"    : (: ask_luan :),
		"��Ħ����": (: ask_shang :),
		"����"    : (: ask_shang :),
		"��Ħ��Ԫ��": (: ask_zhe :),
		"��Ԫ��"    : (: ask_zhe :),
	]));

	create_family("������", 1, "��ɽ��ʦ");

	set_temp("apply/attack", 300);
	set_temp("apply/defense", 300);
	set_temp("apply/damage", 150);
	set_temp("apply/unarmed_damage", 150);

	setup();
	carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}

void attempt_apprentice(object ob)
{
	object me; 
	mapping ob_fam, my_fam;
	string name, new_name;

	if (! permit_recruit(ob))
		return;

	me = this_object();
	my_fam  = me->query("family");

	name = ob->query("name");

	if (! (ob_fam = ob->query("family")) ||
	    ob_fam["family_name"] != "������")
	{
		command("say " + RANK_D->query_respect(ob) +
			"�뱾��������������֪�˻��Ӻ�̸��");
		return;
	}

	if ((string)ob->query("class") != "bonze")
	{
		command("say " + RANK_D->query_respect(ob) +
			"���׼ҵ��ӣ�����������ѧ�ա�");
		return;
	}

	if ((int)ob_fam["generation"] != 36)
	{
		command("say " + RANK_D->query_respect(ob) +
			"��ƶɮ����ҵ���");
		return;
	}

	if ((int)ob->query_int() < 35)
	{
		command("say " + RANK_D->query_respect(ob) + "�������в��㣬"
			"��Ҫ��һ�������������������ķ𷨡�");
	}

	if ((int)ob->query("WPK") > 3)
	{
		command("sigh");
		command("say " + RANK_D->query_respect(ob) + "ɱ¾��̫�أ�"
			"���ʺϼ���ѧϰ�书��");
		return;
	}

	if ((int)ob->query_skill("buddhism", 1) < 180)
	{
		command("say " + RANK_D->query_respect(ob) + "�����ķ�"
			"����ò����������ȶ�����С�");
		return;
	}

	if ((int)ob->query_skill("dodge", 1) < 180)
	{
		command("say " + RANK_D->query_respect(ob) + "�����Ṧ"
			"�������Ƿȱ�������ȿ���������");
		return;
	}

	if ((int)ob->query_skill("force", 1) < 180)
	{
		command("say " + RANK_D->query_respect(ob) + "�����ڹ�"
			"�������Ƿȱ�������ȿ���������");
		return;
	}

	if ((int)ob->query_skill("parry", 1) < 180)
	{
		command("say " + RANK_D->query_respect(ob) + "�����м�"
			"�������Ƿȱ�������ȿ���������");
		return;
	}

	if ((int)ob->query("combat_exp") < 1000000)
	{
		command("say " + RANK_D->query_respect(ob) + "ʵս����"
			"������Ƿȱ�������ȿ���������");
		return;
	}

	command("chat �����ֵ�һ����֮�ţ����Ǵ��ϻ� !");
	name = ob->query("name");
	new_name = "��" + name[2..3];
	NAME_D->remove_name(ob->query("name"), ob->query("id"));
	ob->set("name", new_name);
	NAME_D->map_name(ob->query("name"), ob->query("id"));

	command("say �ӽ��Ժ���ķ�������" + new_name + "��");
	command("recruit " + ob->query("id"));
	return;
}

mixed ask_qingxin()
{
	object me;

	me = this_player();
	if (me->query("can_perform/damo-jian/qingxin"))
		return "�Լ��úö���ϰ�ɣ��μǴȱ�Ϊ����������ã�";

	if (me->query("family/family_name") != query("family/family_name"))
		return RANK_D->query_respect(me) +
		       "�����������ֵ��ӣ��γ����ԣ�";

	if (! me->is_apprentice_of(this_object()))
		return "���з��ҵ��Ӳ��ܴ���������λ" +
		       RANK_D->query_respect(me) + "���¡�";

	if (me->query("shen") < 120000)
		return "�������ڽ�����ħ�����Ȼ�����ڴ˵����ֺα�ѧ����";

	if (me->query_skill("damo-jian", 1) < 200)
		return "��Ĵ�ħ�����������ң��޷�������а��";

	message_vision(HIY "$n" HIY "����$N" HIY
		       "���������ðɣ���������ϸ�ˣ���˵����$N"
		       HIY "��������˵��Щʲô��"NOR"\n",
		       me, this_object());
	command("say ��ס�����ǽ�����ħ�򲻵��ѣ���Ҫ����ʹ�á�");
	tell_object(me, HIG "��ѧ���˴�ħ��������"NOR"\n");
	if (me->can_improve_skill("force"))
		me->improve_skill("force", 160000);
	me->set("can_perform/damo-jian/qingxin", 1);
	return 1;
}

mixed ask_luan()
{
	object me;

	me = this_player();
	if (me->query("can_perform/damo-jian/luan"))
		return "�Լ��úö���ϰ�ɣ��μǴȱ�Ϊ����������ã�";

	if (me->query("family/family_name") != query("family/family_name"))
		return RANK_D->query_respect(me) + "�����������ֵ��ӣ��γ����ԣ�";

	if (! me->is_apprentice_of(this_object()))
		return "���з��ҵ��Ӳ��ܴ���������λ" +
		       RANK_D->query_respect(me) + "���¡�";

	if (me->query("shen") < 120000)
		return "�������ڽ�����ħ�����Ȼ�����ڴ˵����ֺα�ѧ����";

	if (me->query_skill("damo-jian", 1) < 200)
		return "��Ĵ�ħ�����������ң��޷�������а��";

	message_vision(HIY "$n" HIY "����$N" HIY
		       "���������ðɣ���������ϸ�ˣ���˵����$N"
		       HIY "��������˵��Щʲô��"NOR"\n",
		       me, this_object());
	command("say ��ס�����ǽ�����ħ�򲻵��ѣ���Ҫ����ʹ�á�");
	tell_object(me, HIG "��ѧ���˴�ħ���Ľ���"NOR"\n");
	if (me->can_improve_skill("sword"))
		me->improve_skill("sword", 160000);
	me->set("can_perform/damo-jian/luan", 1);
	return 1;
}

mixed ask_shang()
{
	object me;

	me = this_player();
	if (me->query("can_perform/damo-jian/shang"))
		return "�Լ��úö���ϰ�ɣ��μǴȱ�Ϊ����������ã�";

	if (me->query("family/family_name") != query("family/family_name"))
		return RANK_D->query_respect(me) +
		       "�����������ֵ��ӣ��γ����ԣ�";

	if (! me->is_apprentice_of(this_object()))
		return "���з��ҵ��Ӳ��ܴ���������λ" +
		       RANK_D->query_respect(me) + "���¡�";

	if (me->query("shen") < 120000)
		return "�������ڽ�����ħ�����Ȼ�����ڴ˵����ֺα�ѧ����";

	if (me->query_skill("damo-jian", 1) < 200)
		return "��Ĵ�ħ�����������ң��޷�������а��";

	message_vision(HIY "$n" HIY "����$N" HIY
		       "���������ðɣ���������ϸ�ˣ���˵����$N"
		       HIY "��������˵��Щʲô��"NOR"\n",
		       me, this_object());
	command("say ��ס�����ǽ�����ħ�򲻵��ѣ���Ҫ����ʹ�á�");
	tell_object(me, HIG "��ѧ���˴�ħ���񽣡�"NOR"\n");
	if (me->can_improve_skill("force"))
		me->improve_skill("force", 160000);
	me->set("can_perform/damo-jian/shang", 1);
	return 1;
}

mixed ask_zhe()
{
	object me;

	me = this_player();
	if (me->query("can_perform/damo-jian/zhe"))
		return "�Լ��úö���ϰ�ɣ��μǴȱ�Ϊ����������ã�";

	if (me->query("family/family_name") != query("family/family_name"))
		return RANK_D->query_respect(me) +
		       "�����������ֵ��ӣ��γ����ԣ�";

	if (! me->is_apprentice_of(this_object()))
		return "���з��ҵ��Ӳ��ܴ���������λ" +
		       RANK_D->query_respect(me) + "���¡�";

	if (me->query("shen") < 120000)
		return "�������ڽ�����ħ�����Ȼ�����ڴ˵����ֺα�ѧ����";

	if (me->query_skill("damo-jian", 1) < 200)
		return "��Ĵ�ħ�����������ң��޷�������а��";

	message_vision(HIY "$n" HIY "����$N" HIY
		       "���������ðɣ���������ϸ�ˣ���˵����$N"
		       HIY "��������˵��Щʲô��"NOR"\n",
		       me, this_object());
	command("say ��ס�����ǽ�����ħ�򲻵��ѣ���Ҫ����ʹ�á�");
	tell_object(me, HIG "��ѧ���˴�ħ��Ԫ����"NOR"\n");
	if (me->can_improve_skill("force"))
		me->improve_skill("force", 160000);
	me->set("can_perform/damo-jian/zhe", 1);
	return 1;
}
