// shipotian.c

#include <ansi.h>

inherit NPC;

void create()
{
	set_name("ʯ����", ({"shi potian", "shi","potian"}));
	set("title", "���ְ����");
	set("gender", "����");
	set("age", 20);
	set("long", "����Լ��ʮ���꣬����һ�����õ��·���ȴҲ����ס��һ���Ӣ����\n");

	set("attitude", "peaceful");

	set("str", 25);
	set("int", 35);
	set("con", 25);
	set("dex", 25);

	set("qi", 2000);
	set("max_qi", 2000);
	set("jing", 1000);
	set("max_jing", 1000);
	set("neili", 2000);
	set("max_neili", 2000);
	set("jiali", 100);

	set("combat_exp", 1000000);
	set("score", 30000);

	set_skill("force", 100);
	set_skill("taixuan-gong", 150);
	set_skill("unarmed", 100);
	set_skill("dodge", 100);
	set_skill("parry", 100);
	set_skill("begging", 50);
	set_skill("checking", 50);

	map_skill("force", "taixuan-gong");
	map_skill("unarmed", "taixuan-gong");
	map_skill("dodge", "taixuan-gong");
	map_skill("parry", "taixuan-gong");

	set("chat_chance", 1);
	set("chat_msg", ({
		"ʯ����˵��: �������͵���ô�����ˣ�Ҳ��֪�����������������ô���ˡ�\n",
		"ʯ����˵: ������������Ҫ�������ߴ��кô�����\n",
		"ʯ����ͻȻ˵��: ���У��Ҳ����İ��壬��Ҫȥ��������\n",
		"ʯ����ͻȻ˵��: �ӣ��ҵ�������ô������һȺ����ڶ��ء�\n",
	}));
	set("inquiry", ([
		"ʯ����" :  "�����ҵ��ֵܣ���������Ħ���¡�",
		"����"   :  "ѽ����������������ðɡ�",
	]));

	setup();
	carry_object("/clone/misc/cloth")->wear();
}

void destroy(object me, object ob)
{
	destruct(ob);
	return;
}
