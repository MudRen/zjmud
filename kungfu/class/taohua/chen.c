inherit NPC;
#include <ansi.h>;
void create()
{
	set_name( "������" ,({ "chen xuanfeng", "chen" }));
	set("title", "�ڷ�˫ɷ");
	set("nickname", HIY"ͭʬ"NOR);
	set("gender", "����");
	set("age", 35);
	set("long",
	    "�����ǻ�ҩʦ�Ķ����ӣ���Ũü���ۣ���������������׳����ֻ��\n"
	    "��ɫ΢΢���ơ�\n");

	set("attitude", "aggressive");
	set("str", 28);
	set("int", 25);
	set("con", 30);
	set("dex", 25);
	set("shen_type", -1);

	set("max_qi", 3900);
	set("max_jing",1900);
	set("neili", 4700);
	set("max_neili", 4700);
	set("jiali", 100);

	set("combat_exp", 1600000);

	set_skill("claw", 180);
	set_skill("strike", 180);
	set_skill("force", 160);
	set_skill("parry", 180);
	set_skill("dodge", 150);
	set_skill("cuixin-zhang", 180);
	set_skill("jiuyin-baiguzhao", 180);
	set_skill("luoying-xinfa", 160);
	set_skill("anying-fuxiang", 150);

	map_skill("force", "bibo-shengong");
	map_skill("parry", "luoying-shenjian");
	map_skill("dodge", "anying-fuxiang");
	map_skill("claw", "jiuyin-baiguzhao");
	map_skill("strike", "cuixin-zhang");

	prepare_skill("claw", "jiuyin-baiguzhao");
	prepare_skill("strike", "cuixin-zhang");

	create_family("�һ���", 2, "�������");
	set("inquiry", ([
	   "ͭʬ":     "�����ϵ��˶���ô���ҵģ����²��£�����������",
	   "��а":     "������ʦ���Ĵºš�",
	   "����":     "�������ʦ�����ĸ���֮һ���Ǹ��϶��ס�ڰ���ɽ��",
	   "�ϵ�":     "����ү�ѳ��ҵ�����ȥ�ˣ�������һ�ơ�",
	   "��ؤ":     "��ؤͳ����ԭ��ؤ�������Ϊǿ��",
	   "���߹�":   "���߹��书��ǿ�����ҽ̻������С������ʮ���ƣ��ɺޣ�",
	   "����":     "������ʦ���Ķ�Ů�����ǵ������ԡ�",
	   "÷����":   "�����ҵ�ʦ�ã�Ҳ���ҵ����ҡ�",
	   "������":   "��������ô�����ǰ׳հ���",
	   "��ҩʦ":   "������ʦ����"]) );
	setup();
	carry_object("/clone/cloth/bupao")->wear();
}

void attempt_apprentice(object ob)
{
	command("say ���ٷ��ң������");
}

