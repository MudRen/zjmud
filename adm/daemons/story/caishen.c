// story:caishen ����

#include <ansi.h>

int give_gift(string money, int amount, string name);

static mixed *story = ({
	"��С������·��ꡣ",
	"�������·��",
	"С����ƾʲô��",
	"����񣺷ϻ���ƾ�ұ�����Ǯ��",
	"С������������ͭ�壬�������˳�ȥ���ߺߵ�������",
	(: give_gift, "coin", 10 + random(5), "ͭ��" :),
	"�����һ����Ц������һЩ�������˳�ȥ��",
	(: give_gift, "silver", 10 + random(5), "����" :),
	"С�������˰��죬�ͳ�һЩ�ƽ�ҧҧ�����˳�ȥ����������ѽ��",
	(: give_gift, "gold", 1 + random(2), "�ƽ�" :),
	"�����ǺǴ�Ц������������Ʊ����ƮƮ�ķ��˳�ȥ��",
	(: give_gift, "cash", 1, "��Ʊ" :),
	"С����������ɫ������������Ǯ��������Ǯ������·������·��",
});

void create()
{
	seteuid(getuid());
}

mixed query_story_message(int step)
{
	return step < sizeof(story) ? story[step] : 0;
}

int give_gift(string money, int amount, string name)
{
	STORY_D->give_gift("/clone/money/" + money, amount,
			   HIM "\n��ž����һ��һЩ" + name + "��������ǰ��"NOR"\n");
	return 1;
}
