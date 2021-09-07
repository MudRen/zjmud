// story:master ��ʦ�ۻ�

#include <ansi.h>

static string *char_id;
static string *char_name;
static string winner_name;
static string winner_id;
static string ann_name;
static string ann_id;

int   get_winner();
mixed give_gift();
int   rob_gift();
int   select_characters();

static mixed *story = ({
	"$1[$I1]���ã���������������ۻ�ɽ�����غ��ѣ��ɿ������⡣",
	"$2[$I2]���ţ�����ȥ��Ҳ���ض�˵�ˣ��˴�����Ϊ�˽����Ͻ��ճ��ֵ�"
	HIM "�������嵤" NOR WHT "һ�¡�",
	"$3[$I3]����˵�˵�ǧ��һ���������Ժ��������ƽ��ʮ�깦����",
	"$4[$I4]���ٺ٣�ֻ��ÿ�γ���Ū�ý����ȷ�Ѫ�꣬���ð�����",
	"$5[$I5]�����������ټ���λ��������ѣ������������֡�",
	"$2[$I2]��Ҳ�ǣ����������Ǹ�������С��ȥ�����ν���鰵Ͷ��",
	"$5[$I5]���������������Ҷᣬ����ʵ���ǿ�����ȥ��������Գ���ȡ������",
	"$1[$I1]���������ã�����ˡ�",
	"$5[$I5]��ֻ�Ǵ�������Ҳ����óȻ�Ծӣ��������λ����ɽ�۽����Ծ����������",
	"$3[$I3]���ϻ����ض�˵����αȷ���",
	"$4[$I4]�����Ǹ��Ծ��գ�˭��ѹ���Է������ǵ�������Σ�",
	"$2[$I2]���ðɣ�$4���Լ��ǡ�",
	"...",
	"�����...",
	"��������...",
	"���ֺ���...",
	"��������...",
	"...",
	(: get_winner :),
	"$a̾������������������������$w�书��ǿ����ʤһ�ﰡ��",
	"$wǫ�������������λ���ֲ��������������۽�󿪣���֪�������졣",
	"$a[$Ia]������ǫ�ã�������Ӧ��$w���У��������Ⱑ��",
	(: give_gift :),
	"$w[$Iw]�����ߣ����У�",
	"�Ǻ�Ӱ��Ȼ������$w����һ�ƣ�ֻ���$w�ۻ����ң���Ѫ��ӿ��",
	"��Ӱ������Ц��ƮȻ��ɽ��ȥ��",
	"$w��Ϣ���ã��������³�һ��������������������������ҿ�������$6��",
	(: rob_gift :),
});

void create()
{
	seteuid(getuid());

	if (uptime() < 86400)
	{
		destruct(this_object());
		return;
	}

	ann_id = 0;
	ann_name = 0;
	winner_id = 0;
	winner_name = 0;
	if (! select_characters())
	{
		STORY_D->remove_story("master");
		destruct(this_object());
		return;
	}
}

string prompt() { return HIG "����ɽ�۽���" NOR; }

int select_characters()
{
	object *obs;
	object ob;
	int i;

	obs = filter_array(all_interactive(),
			   (: ! wizardp($1) && ultrap($1) && living($1):));
	if (sizeof(obs) < 6)
		return 0;

	char_id = allocate(6);
	char_name = allocate(6);
	for (i = 0; i < 6; i++)
	{
		ob = obs[random(sizeof(obs))];
		char_id[i] = ob->query("id");
		char_name[i] = ob->name(1);
		obs -= ({ ob });
	}

	return 1;
}

mixed query_story_message(int step)
{
	mixed msg;

	if (step >= sizeof(story))
		return 0;

	msg = story[step];
	if (functionp(msg)) msg = evaluate(msg);
	if (stringp(msg))
	{
		msg = replace_string(msg, "$1", char_name[0]);
		msg = replace_string(msg, "$I1", char_id[0]);
		msg = replace_string(msg, "$2", char_name[1]);
		msg = replace_string(msg, "$I2", char_id[1]);
		msg = replace_string(msg, "$3", char_name[2]);
		msg = replace_string(msg, "$I3", char_id[2]);
		msg = replace_string(msg, "$4", char_name[3]);
		msg = replace_string(msg, "$I4", char_id[3]);
		msg = replace_string(msg, "$5", char_name[4]);
		msg = replace_string(msg, "$I5", char_id[4]);
		msg = replace_string(msg, "$6", char_name[5]);
		msg = replace_string(msg, "$I6", char_id[5]);
		if (ann_name && ann_id)
		{
			msg = replace_string(msg, "$a", ann_name);
			msg = replace_string(msg, "$Ia", ann_id);
		}
		if (winner_name && winner_id)
		{
			msg = replace_string(msg, "$w", winner_name);
			msg = replace_string(msg, "$Iw", winner_id);
		}
	}
	return msg;
}

int get_winner()
{
	int i;

	i = random(5);
	winner_name = char_name[i];
	winner_id = char_id[i];
	do
	{
		i = random(5);
		ann_id = char_id[i];
		ann_name = char_name[i];
	} while (ann_id == winner_id);

	return 1;
}

mixed give_gift()
{
	object gob;
	object gift;

	gob = find_player(winner_id);
	if (random(2))
	{
		CHANNEL_D->do_channel(this_object(), "rumor",
				      "��˵�����ʦ�ڻ�ɽ�ۻᣬ��" +
				      "�������嵤����" + winner_name + "��");
		STORY_D->remove_story("master");
		if (gob)
		{
			gift = new("/clone/ultra/xuanhuang");
			if (gift) gift->move(gob, 1);
		}
		return 0;
	}

	return "һ����Ӱ�ӹ���һ�����صĻ���$a�ı��ģ�$a���һ�����³�һ����Ѫ��";
}

int rob_gift()
{
	object rob;
	object gift;

	rob = find_player(char_id[5]);
	CHANNEL_D->do_channel(this_object(), "rumor",
			      "��˵" + char_name[5] + "�������ʦ���ж�����"
			      "�������嵤��");
	STORY_D->remove_story("master");
	if (rob)
	{
		gift = new("/clone/ultra/xuanhuang");
		if (gift) gift->move(rob, 1);
	}
	return 0;
}
