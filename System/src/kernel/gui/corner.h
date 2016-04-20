/* 
 * The Corner data structure represents corner value of
 * one view or sheet if it is rendered to be round-corner.
 * It contains leftTop, rightTop, leftBtm, rightBtm, total 
 * four vectors.
 */
typedef struct Corner
{
    u32 leftTop;

    u32 rightTop;

    u32 leftBtm;

    u32 rightBtm;

} Corner;
