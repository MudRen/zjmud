inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

#include <ansi.h>
#include "gaibang.h"

void kicking(object ob);

void create()
{
	set_name("������", ({"bai shijing", "bai", "shijing"}));
	set("title", "ؤ��Ŵ�����");
	set("nickname", "ִ������");
	set("gender", "����");
	set("age", 55);
	set("long", 
		"��������ؤ���ִ�����ϣ��������������Ѿá�\n");
	set("attitude", "peaceful");
	set("class", "beggar");
	set("no_get", "1");
	
	set("str", 28);
	set("int", 24);
	set("con", 24);
	set("dex", 25);

	set("qi", 3000);
	set("max_qi", 3000);
	set("jing", 1500);
	set("max_jing", 1500);
	set("neili", 4800);
	set("max_neili", 4800);
	set("jiali", 100);
	
	set("combat_exp", 1200000);
	
	set_skill("force", 195);
	set_skill("jiaohua-neigong", 195);
	set_skill("hand", 180);
	set_skill("chansi-shou", 180);
	set_skill("strike", 170);
	set_skill("xiaoyaoyou", 170);
	set_skill("dodge", 170);
	set_skill("feiyan-zoubi", 170);
	set_skill("parry", 190);
	set_skill("staff", 170);
	set_skill("jiaohua-bangfa", 170);
	set_skill("begging", 80);
	set_skill("checking", 150);
	set_skill("training", 120);
	
	map_skill("force", "jiaohua-neigong");
	map_skill("hand", "chansi-shou");
	map_skill("strike", "xiaoyaoyou");
	map_skill("staff", "jiaohua-bangfa");
	map_skill("dodge", "feiyan-zoubi");

	prepare_skill("hand", "chansi-shou");

	create_family("ؤ��", 18, "�Ŵ�����");
	setup();
}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob))
		return;

	if ((int)ob->query_str() < 26)
	{
		command("say ����ؤ�������һ���Ը���Ϊ����" + 
		RANK_D->query_respect(ob) + "����̫�����ƺ�����ѧؤ��Ĺ���");
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
}

int recognize_apprentice(object me)
{
	if (me->query("family/family_name") != query("family/family_name"))
		return 0;

	if (me->query("beggarlvl") < 9)
		return 0;

	return 1;
}
