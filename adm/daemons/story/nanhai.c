// story:nanhai �Ϻ���˵

#include <ansi.h>

int give_gift(string name);

static mixed *story = ({
	"������������������¡��",
	"���񣺲�����������Х�����������Ӱ�������",
	"������������������¡��",
	"�ۼ���ˮ��ס�����ӣ�����ǳ̲����������",
	"����",
	"�Ϻ�������Ȼ����˫�ۣ��������η����",
	"������������",
	"����ȵ�����ԭ������������ϣ������˷����ˣ���Ҫ���񣬳���һ�ƣ���",
	"ž��",
	"�Ϻ����ԣ��ٺٺٺ٣�ʲô����ô��ʶ�ô���",
	"����ֱ����ۻ����ң���Ѫ��ӿ���������������������꣬��Ȼ��˲��á�",
	"�������룬����Ͻ����̸ǣ���������Ͻ��ϻ�ɽ�Ҷ����������ͷ���ѹ�������ɽ�ϣ��е���",
	(: give_gift, "nanhai" :),
	"��˵�Ϻ�����(monster dragon)�س��󺣣����˼��˷����ˡ�",
});

string prompt() { return HIM "���񻰴�˵��" NOR; }

void create()
{
	seteuid(getuid());
}

mixed query_story_message(int step)
{
	return step < sizeof(story) ? story[step] : 0;
}

int give_gift(string name)
{
	object ob;

	ob = new(CLASS_D("misc/") + name);
	if (! objectp(ob))
		return 0;

	NPC_D->place_npc(ob);
	if (! objectp(environment(ob)))
	{
		destruct(ob);
		return 0;
	}

	CHANNEL_D->do_channel(find_object(STORY_D), "sys",
			      ob->name() + "������" + environment(ob)->short() +
			      "(" + base_name(environment(ob)) + ")��");
	return 1;
}
