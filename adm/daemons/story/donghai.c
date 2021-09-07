// story:donghai ��������˵

#include <ansi.h>

int give_gift(string name);

static mixed *story = ({
	"��߸����ϴ��ȥ�ˡ�",
	"��������ȥ��ȥ�����ٸ������¡�",
	"......",
	"��߸��ϴϴͷ��",
	"��߸�����ţ�",
	"��߸�����Ҵ�걳�������ҵ�С������...",
	"������������������",
	"�����������ҵ��죬��ô�ε���ô������",
	"Ϻ��з����������࣬�������ˣ�",
	"��������ร��ϰ־�������",
	"��̫�ӣ����д���һ�������˸��ƻ�������ȥ������ף�",
	"�����ã��ۣ���˧ѽ��",
	"......",
	"��̫�ӣ�أ��С�ӣ������������������ڵĵط���",
	"��߸��ʲô�ˣ�������ϴ�裿����һ��Ȧ��",
	"ž��",
	"���ϣ�",
	(: give_gift, "donghai" :),
	"��˵��̫��(prince of dragon)����߸������ͻ�������䷲�䡣",
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
