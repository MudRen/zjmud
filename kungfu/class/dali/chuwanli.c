// chuwanli.c ������

#include <ansi.h>

inherit NPC;
inherit F_GUARDER;

void create()
{
	set_name("������", ({ "chu wanli", "chu" }));
	set("title",  "���������" );
	set("long", "���Ǵ�����Ĵ���֮һ�������£�����Ӣ�����ˡ��ֳ�һ�����ˡ�\n");
	set("gender", "����");
	set("age", 33);
	set("class", "officer");
	set("attitude", "friendly");
	set("shen_type", 1);
	set("per", 25);
	set("str", 20);
	set("int", 20);
	set("con", 25);
	set("dex", 25);
	
	set("max_qi", 1800);
	set("max_jing", 900);
	set("neili", 1900);
	set("max_neili", 1900);
	set("jiali", 45);
	set("combat_exp", 310000);
	set("score", 8000);

	set_skill("force", 80);
	set_skill("dodge", 80);
	set_skill("parry", 80);
	set_skill("sword", 80);
	set_skill("staff", 80);
	set_skill("cuff", 75);
	set_skill("jinyu-quan", 75);
	set_skill("shaolin-xinfa", 80);
	set_skill("tiannan-step", 70);
	set_skill("duanjia-sword", 80);
	set_skill("literate", 30);

	map_skill("force", "shaolin-xinfa");
	map_skill("dodge", "tiannan-step");
	map_skill("sword", "duanjia-sword");
	map_skill("staff", "duanjia-sword");
	map_skill("parry", "duanjia-sword");
	prepare_skill("cuff", "jinyu-quan");

	set("coagents", ({
		([ "startroom" : "/d/dali/neitang",
		   "id"	: "duan zhengchun", ]),
	}));

	set("guarder", ([
		"refuse_home" : "$N��ס$n�����Բ�����ү������˶μҾ�Ī������\n",
		"refuse_other": "$Nһ����ס$n���ȵ��������˵ȣ��������ڡ�\n",
		"refuse_carry": "$N����Ц����$n�����ɷ�... �㱳���˷����ٽ�������\n",
	]));

	setup();
	carry_object("/d/dali/npc/obj/junfu")->wear();
	carry_object(__DIR__"obj/diaogan")->wield();
	add_money("silver", 10);

	create_family("���ϻ���", 0, "����");
}
