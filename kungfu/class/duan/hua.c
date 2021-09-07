#include <ansi.h>
#include "duan.h"

inherit NPC;
inherit F_MASTER;

void create()
{
	set_name("������", ({ "hua hegen", "hua", "hegen" }));
	set("title", "�������������" );
	set("nickname", HIW "˾ͽ" NOR);
	set("long", @LONG
���Ǵ��������֮һ����˾ͽ��������������ƶ
�����ֽ��ڴ����λ��������δ����ʱ���ɲ���ȴ
�ǵ�Ĺ��صĹ�����  ���ó��ı�����͵��������
�ֵķ�Ĺ����Щ�����������󣬱������챦��ѳ�ᣬ
�������Ӽ�Զ���ھ�ص���ͨ���Ĺ��Ȼ���ȡ��
�������һ����ޣ�ȴ�ɴ˶���δΪ�˷�������
һ��������һ�أ��ڹ�ľ�еõ���һ��ѳ����书
�ؾ���������ϰ��������һ��׿�������Ź��򣬱�
���������¼���Ӫ�������������ۣ������湦����
������˾ͽְ֮��
LONG);
	set("gender", "����");
	set("age", 46);
	set("class", "officer");
	set("attitude", "friendly");
	set("shen_type", 1);
	set("str", 30);
	set("int", 20);
	set("con", 25);
	set("dex", 25);

	set("max_qi", 3000);
	set("max_jing", 1800);
	set("neili", 3200);
	set("max_neili", 3200);
	set("jiali", 150);
	set("combat_exp", 1500000);
	set("score", 10000);

	set_skill("force", 180);
	set_skill("duanshi-xinfa", 180);
	set_skill("dodge", 180);
	set_skill("tiannan-step", 180);
	set_skill("cuff", 160);
	set_skill("jinyu-quan", 160);
	set_skill("strike", 160);
	set_skill("wuluo-zhang", 160);
	set_skill("claw", 180);
	set_skill("yuezhao-gong", 180);
	set_skill("parry", 180);
	set_skill("literate", 120);
	set_skill("martial-cognize", 160);

	map_skill("force", "duanshi-xinfa");
	map_skill("dodge", "tiannan-step");
	map_skill("cuff", "jinyu-quan");
	map_skill("strike", "wuluo-zhang");
	map_skill("claw", "yuezhao-gong");
	map_skill("parry", "yuezhao-gong");

	prepare_skill("claw", "yuezhao-gong");

	create_family("���ϻ���", 15, "˾ͽ");

	set("chat_chance_combat", 120);
	set("chat_msg_combat", ({
		(: perform_action, "claw.shi" :),
		(: exert_function, "recover" :),
	}));

	setup();
	carry_object("/d/dali/npc/obj/junfu")->wear();
	add_money("silver", 10);
}

void attempt_apprentice(object ob)
{
	if (! permit_recruit(ob))
		return;

	command("smile");
	command("say ���ӵ��º�����ˣ�ֻҪ���·Ը�����һ�����ǡ�");
	command("say �����Ӳ������������ﵹ����һ��צ�����Դ������㡣");

	return;
}

int recognize_apprentice(object ob, string skill)
{
	if (ob->query("family/family_name") != "���ϻ���")
	{
		command("sneer");
		command("say ��������ز���ʶ����֪���´˻��Ӻ�˵��");
		return -1;
	}

	if (skill != "yuezhao-gong" && skill != "claw")
	{
		command("say ����ƽ��������צ����Ϊ��������Ļ�������ү���Խ���ɡ�");
		return -1;
	}

	if (! ob->query_temp("can_learn/huahegen"))
	{
		command("nod");
		command("say ��Ȼ��������ϰ�䣬�������߾����ܴ��ڡ�");
		ob->set_temp("can_learn/huahegen", 1);
	}
	return 1;
}

